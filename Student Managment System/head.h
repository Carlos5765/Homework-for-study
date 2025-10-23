#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<filesystem>
#include <map>
#include <stdexcept>

using namespace std;

class PasswordError : public std::runtime_error {//错误处理类，用以向程序反馈错误
public:
	PasswordError(const std::string& message) : std::runtime_error(message) {}
};

enum user_type {//定义用户的两种类型
	teacher,
	student
};

class Student {//记录学生基本信息
protected:
	string name, id, school_id, major;
	char gender;
	int age;
public:
	string Get_Name() {
		return name;
	}
	string Get_School_Id() {
		return school_id;
	}
	string Get_Major () {
		return major;
	}
	friend istream& operator>>(istream& input, Student& s);
	friend ostream& operator<<(ostream& output, const Student& s);
};

istream& operator>>(istream& input, Student& s) {
	string line;
	getline(input, line);

	//将一整行数据分段
	int space1 = line.find(' ');
	int space2 = line.find(' ', space1 + 1);
	int space3 = line.find(' ', space2 + 1);
	int space4 = line.find(' ', space3 + 1);
	int space5 = line.find(' ', space4 + 1);

	//检测到不符合输入预期就自动改变输入流状态为错误
	if (space1 == string::npos || space2 == string::npos ||
		space3 == string::npos || space4 == string::npos || space5 == string::npos) {
		cout << "格式错误(需6个字段（空格分隔))或文件已到末尾" << endl;
		input.setstate(ios::failbit);
		return input;
	}

	//用分割开的数据给对应的各个变量赋值
	s.name = line.substr(0, space1);
	s.gender = toupper(line[space1 + 1]);
	s.age = stoi(line.substr(space2 + 1, space3 - space2 - 1));
	s.school_id = line.substr(space3 + 1, space4 - space3 - 1);
	s.id = line.substr(space4 + 1, space5 - space4 - 1);
	s.major = line.substr(space5 + 1);

	//检测到不符合输入预期就自动改变输入流状态为错误
	if (s.gender != 'M' && s.gender != 'F') {
		cout << "性别错误（M/F）！" << endl;
		input.setstate(ios::failbit);
		return input;
	}
	if (s.age < 0 || s.age > 150) {
		cout << "年龄错误（0-150）！" << endl;
		input.setstate(ios::failbit);
		return input;
	}
	if (s.school_id.size() != 6) {
		cout << "学号错误（6位）！" << endl;
		input.setstate(ios::failbit);
		return input;
	}
	if (s.id.size() != 18 && s.id.size() != 19) {
		cout << "身份证号错误（18/19位）！" << endl;
		input.setstate(ios::failbit);
		return input;
	}
	if (s.major.empty()) {
		cout << "专业不能为空！" << endl;
		input.setstate(ios::failbit);
		return input;
	}

	return input;
}

ostream& operator<<(ostream& output, const Student& s) {
	output << s.name << " " << s.gender << " " << s.age << " "
		<< s.school_id << " " << s.id << " " << s.major;  // 添加major输出
	return output;
}

class Menu {
protected:
	user_type type;
	bool log;
public:
	Menu() : log(false) {//将用户类型选择放在Menu的构造函数内，这样无参创建对象时会自动调用该函数
		int input;
		while (true) {
			cout << "请输入您的用户类型（1.学生 0.老师）" << endl;
			if (cin >> input && (input == 0 || input == 1)) {
				type = static_cast<user_type>(input);
				break;
			}
			cout << "输入错误！请输入合法的数字" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
	Menu(user_type t,bool l):type(t),log(l){}
	user_type Get_Type() {
		return type;
	}
	virtual void Log_In(){}
	virtual bool Get_log() {
		return log;
	}
	virtual void Menu_Show(){}
	virtual void Fuction_Jump(int){}
	virtual void Information_Entry(){}
	//设置虚函数使得基类指针能指向子类对象
};

class Student_menu :public Menu{
	Student* user;
public:
	Student_menu() :user(NULL), Menu(student,false) {}
	~Student_menu() {
		delete user;
	}

	void Log_In() {//打开个人信息文档比对信息，如果学号与姓名相吻合就记录成功登录
		string name, school_id;
		fstream file("self_information.txt", ios::in | ios::out);
		if (!file) {
			cout << "打开文件失败" << endl;
			system("pause");
			file.close();
		}
		else {
			Student s;
			bool j = false;
			while (true) {
				system("cls");
				cout << "请输入姓名" << endl;
				cin >> name;
				cout << "请输入学号" << endl;
				cin >> school_id;
				while (file >> s) {
					if (s.Get_Name() == name && s.Get_School_Id() == school_id) {
						j = true;
						break;
					}
				}
				if (j) {
					system("cls");
					cout << "登陆成功" << endl;
					system("pause");
					break;
				}
				else {
					cout << "姓名或学号错误，请重新输入" << endl;
					system("pause");
				}
			}
			log = true;
			user = new Student(s);
		}
	}

	void Menu_Show() {
		cout << "在此展示所有信息" << endl;
	}

	void Fuction_Jump(int i) {//根据学号打开不同的文档读取信息并打印出来
		cout << "个人信息" << endl;
		cout << *user << endl;
		string major = user->Get_Major() + ".txt";
		fstream file(major, ios::in | ios::out);
		int number;
		if (!file) {
			file.close();
		}
		else {
			string* subject;
			cout << "成绩信息" << endl;
			int score;
			file >> number;
			string file_school_id;
			subject = new string[number];
			for (int n = 0;n < number;n++) {
				file >> subject[n];
				cout << subject[n];
				if (n != number - 1)
					cout << " ";
				else
					cout << "\n";
			}
			while (file >> file_school_id) {
				if (file_school_id == user->Get_School_Id()) {
					cout << file_school_id << " ";
					for (int n = 0;n < number;n++) {
						file >> score;
						cout << score;
						if (n != number - 1)
							cout << " ";
						else
							cout << "\n";
					}
					break;
				}
				for (int n = 0;n < number;n++) {
					file >> score;
				}
			}
			file.close();
			delete[] subject;
		}
		fstream file1("honour.txt", ios::in | ios::out);
		if (!file1) {
			file1.close();
		}
		else {
			cout << "成就信息" << endl;
			int file_id;
			while (file1 >> file_id) {
				string* subject1;
				string str = to_string(file_id);
				file1 >> number;
				subject1 = new string[number];
				if (str != user->Get_School_Id()) {
					for (int n = 0;n < number;n++) {
						file1 >> subject1[n];
					}
				}
				else {
					cout << file_id << " ";
					for (int n = 0;n < number;n++) {
						file1 >> subject1[n];
						cout << subject1[n];
						if (n != number - 1)
							cout << " ";
						else
							cout << "\n";
					}
					break;
				}
				delete[] subject1;
			}
			file1.close();
		}
		cout << "按任意键退出" << endl;
		system("pause");
		log = false;
	}
};

class Teacher_menu :public Menu {
	Student* user;
public:
	Teacher_menu():user(NULL),Menu(teacher,false){}
	~Teacher_menu() {
		delete user;
	}
	void Log_In() {//设置输入次数上限为3，如在规定次数内输入正确密码，就更改登陆状态log为ture，反之就进行错误报告
		string password;
		int attempts = 0;
		const int MAX_ATTEMPTS = 3;

		try {
			while (true) {
				cout << "请输入教师登录密码（最多尝试" << MAX_ATTEMPTS << "次）:" << endl;
				cin >> password;
				attempts++;

				if (password == "123456") {
					cout << "登录成功!" << endl;
					system("pause");
					break;
				}

				if (attempts >= MAX_ATTEMPTS) {
					throw PasswordError("密码错误次数过多，登录失败");
				}

				system("cls");
				cout << "密码错误！你已尝试 " << attempts << " 次，还剩 " << (MAX_ATTEMPTS - attempts) << " 次机会" << endl;
			}
			log = true;
		}
		catch (const PasswordError& e) {
			cout << "错误: " << e.what() << endl;
			system("pause");
			log = false; 
		}
	}

	bool Get_log() {
		return log;
	}

	void Menu_Show() {
		cout << "按下对应数字使用对应功能" << endl;
		cout << "1.修改信息 2.查看信息 0.退出" << endl;
	}

	void Fuction_Jump(int jur) {
		switch (jur) {
		case 1:
			Information_Entry();
			break;
		case 2:
			Information_Viewing();
			break;
		case 0:
			log = false;
			break;
		default: {
			cout << "错误输入!请输入合法的数字" << endl;
			system("pause");
		}
		}
	}

	void Information_Entry() {
		bool control = false;
		while (true) {
			system("cls");
			cout << "输入对应数字录入对应信息" << endl;
			cout << "1.录入个人信息 2.录入成绩信息 3.录入荣誉信息 4.删改个人信息 5.删改成绩信息 6.删改荣誉信息 0.退出" << endl;
			int jur;
			cin >> jur;
			if (cin.fail()) {//清空缓冲区
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "输入错误！请重新输入数字。" << endl;
				system("pause");
				continue;
			}
			cin.ignore(10000, '\n');
			switch (jur) {
			case 1: {//打开self_information.txt，在屏幕上利用重载的>>录入信息，按格式存放在文档中
				int m;
				ofstream file("self_information.txt", ios::app);
				if (!file) {
					cout << "错误！打开文件失败" << endl;
					break;
				}
				system("cls");
				while (true) {
					cout << "请输入学生信息 (格式：姓名 性别 年龄 学号 身份证号 专业): " << endl;
					Student s;
					if (cin >> s) {
						cout << "学生信息录入成功！" << endl;
					}
					else {
						cout << "录入失败，请检查格式并重试。" << endl;
						cin.clear();
						cout << "按下回车键重新输入" << endl;
						cin.ignore(10000, '\n');
						continue;
					}
					cout << "录入成功" << endl;
					file << s << endl;
					cout << "如要继续输入，请按1；如要退出，请按0" << endl;
					cin >> m;
					cin.ignore(10000, '\n');
					system("cls");
					if (m == 0)
						break;
				}
				cout << "已成功退出" << endl;
				system("pause");
				break;
			}
			case 2: {
				system("cls");
				int number=0;
				string textname;
				cout << "请输入专业名称（中文）" << endl;
				cin >> textname;
				textname += ".txt";
				vector<string> subject;
				if (!std::filesystem::exists(textname) || !std::filesystem::is_regular_file(textname)) {//检验是否有该专业的文件
					ofstream file(textname, ios::app);
					if (!file) {
						cout << "错误！打开文件失败" << endl;
						break;
					}
					system("cls");
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "请输入科目（按行输入，输入0完成输入）：" << endl;
					string line = "无";
					while (getline(cin, line) && !line.empty()) {//没有该专业文件的情况下，创建文件并读入科目信息
						if (line == "0")
							break;
						subject.push_back(line);
						number++;
						cout << "录入成功" << endl;
					}
					file << number << " ";
					system("cls");
					for (int n = 0;n < number;n++) {//依次在文件内录入
						file << subject[n];
						if (n != number - 1) {
							file << " ";
						}
						else {
							file << "\n";
						}
					}
					file.close();
				}
				else {
					ifstream file(textname);
					if (!file) {
						cout << "错误！打开文件失败" << endl;
						break;
					}
					system("cls");
					file >> number;
					for (int n = 0;n < number;n++) {
						string str;
						file >> str;
						subject.push_back(str);
					}
					file.close();
				}
				ofstream file(textname, ios::app);
				cout << "请按如下科目顺序录入成绩，格式为：学号 第一科成绩 第二科成绩 第三科成绩……" << endl;//如文件已存在，向文件末尾追加信息
				for (int n = 0;n < number;n++) {
					cout << subject[n];
					if (n != number - 1) {
						cout << " ";
					}
					else {
						cout << "\n";
					}
				}
				cout << "如输入完成要退出，请按0后按回车" << endl;
				while (true) {
					string school_id;
					int score;
					cin >> school_id;
					if (school_id == "0")
						break;
					else
						file << school_id << " ";
					for (int n = 0;n < number;n++) {
						cin >> score;
						file << score;
						if (n != number - 1)
							file << " ";
						else
							file << "\n";
					}
					getchar();
				}
				break;
			}
			case 3: {
				system("cls");
				int id, file_id, number = 0, file_number;
				string* file_honour = new string;
				bool jur = false;
				if (!std::filesystem::exists("honour.txt") || !std::filesystem::is_regular_file("honour.txt")) {//检验honour.txt文件是否存在，如不存在则创建文件
					ofstream file("honour.txt", ios::app);
					file.close();
				}
				cout << "请输入您要录入荣誉信息的学号" << endl;
				cin >> id;
				fstream file("honour.txt", ios::in | ios::out);
				if (!file) {
					cout << "错误！打开文件失败" << endl;
					break;
				}
				while (true) {//检验文件内有无该学号信息
					file >> file_id;
					if (file.eof()) {
						jur = true;
						break;
					}
					file >> file_number;
					file_honour = new string[file_number];
					for (int n = 0;n < file_number;n++) {
						file >> file_honour[n];
					}
					if (file_id == id)//如果有该学号信息，则用file_honour数组记录已存在荣誉
						break;
				}
				file.close();
				if (jur) {//不存在该学号信息就在末尾追加信息
					ofstream file("honour.txt", ios::app);
					file << id << " ";
					vector<string> h;
					string h1;
					cout << "请输入录入的荣誉（按0结束）" << endl;
					while (true) {
						cin >> h1;
						if (h1 == "0")
							break;
						h.push_back(h1);
						number++;
					}
					file << number << " ";
					for (int n = 0;n < number;n++) {
						file << h[n];
						if (n == number - 1)
							file << "\n";
						else
							file << " ";
					}
					cout << "修改成功" << endl;
					system("pause");
					file.close();
				}
				else {//如有学号信息，则在文件末尾把已存在荣誉信息和新录入荣誉信息录入
					ofstream temp_file("temp_honour.txt", ios::app);
					fstream file("honour.txt", ios::in | ios::out);
					string str;
					int temp_id, temp_number;
					while (true) {
						file >> temp_id;
						if (file.eof())
							break;
						file >> temp_number;
						if (temp_id != id) {
							temp_file << temp_id << " " << temp_number << " ";
							for (int n = 0;n < temp_number;n++) {
								file >> str;
								temp_file << str;
								if (n == temp_number - 1)
									temp_file << "\n";
								else
									temp_file << " ";
							}
						}
						else {
							vector<string> ppp;
							cout << "当前信息为：" << endl;
							cout << id << " ";
							for (int n = 0;n < temp_number;n++) {
								file >> str;
								ppp.push_back(str);
								cout << str;
								if (n != temp_number - 1)
									cout << " ";
								else
									cout << "\n";
							}
							temp_file << id << " ";
							cout << "请输入录入的荣誉（按0结束）" << endl;
							while (true) {
								cin >> str;
								if (str == "0")
									break;
								number++;
								ppp.push_back(str);
							}
							temp_file << number + file_number << " ";
							for (int m = 0;m < number + file_number;m++) {
								temp_file << ppp[m];
								if (m != number + file_number - 1) {
									temp_file << " ";
								}
								else {
									temp_file << "\n";
								}
							}
						}
					}
					cout << "修改成功" << endl;
					system("pause");
					temp_file.close();
					file.close();
					filesystem::remove("honour.txt");
					filesystem::rename("temp_honour.txt", "honour.txt");
				}
				break;
			}
			case 4: {
				while (true) {
					system("cls");
					bool find = false;
					int jur1, jur2, jur3;
					cout << "1.修改个人信息 2.删除个人信息 0.退出" << endl;
					cin >> jur1;
					if (jur1 == 0)
						break;
					if (jur1 != 1 && jur1 != 2) {
						cout << "请输入合法数字" << endl;
						system("pause");
						continue;
					}

					fstream file("self_information.txt", ios::in | ios::out);
					ofstream temp_file("temp_self_information.txt", ios::app);
					if (!file.is_open() || !temp_file.is_open()) {
						cout << "无法打开文件！" << endl;
						file.close();
						temp_file.close();
						system("pause");
						break;
					}
					system("cls");
					cout << "1.输入名字修改信息 2.输入学号修改信息" << endl;
					cin >> jur2;
					if (jur2 == 1) {//根据选择操作类型和检索的信息类型用不同的方式读取数据
						system("cls");
						string name;
						Student student, s;
						cout << "请输入姓名" << endl;
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						cin >> name;
						while (file >> student) {//检索该名字的信息存不存在
							if (name != student.Get_Name()) {
								temp_file << student << "\n";
							}
							else {
								s = student;
								find = true;
							}
						}
						if (find) {//找到信息后，先新开一临时文件把除要修改的信息外的信息录入，最后根据之前的选择进行操作，如果选删除则不去在临时文件中录入该消息，如选修改则允许用户输入新的数据录入到文件末尾
							cout << "当前信息：" << endl;
							cout << s << endl;
							if (jur1 == 1) {
								cout << "输入新的数据：" << endl;
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								cin >> s;
								temp_file << s << "\n";
								temp_file.close();
								file.close();
								filesystem::remove("self_information.txt");
								filesystem::rename("temp_self_information.txt", "self_information.txt");
							}
							else if (jur1 == 2) {
								cout << "是否确定删除（1.确定 2.返回）" << endl;
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								cin >> jur3;
								while (true) {
									if (jur3 == 1) {
										temp_file.close();
										file.close();
										filesystem::remove("self_information.txt");
										filesystem::rename("temp_self_information.txt", "self_information.txt");
										cout << "删除成功" << endl;
										system("pause");
										break;
									}
									else if (jur3 == 2) {
										temp_file.close();
										file.close();
										filesystem::remove("temp_self_information.txt");
										system("pause");
										break;
									}
									else
										cout << "请输入合法数字" << endl;
										system("pause");
								}
							}
						}
						else {
							cout << "未找到相关信息" << endl;
							file.close();
							temp_file.close();
							filesystem::remove("temp_self_information.txt");
							system("pause");
						}
					}
					else if (jur2 == 2) {//原理同上
						system("cls");
						string id;
						Student student, s;
						cout << "请输入学号" << endl;
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						cin >> id;
						while (file >> student) {
							if (id != student.Get_School_Id()) {
								temp_file << student << "\n";
							}
							else {
								s = student;
								find = true;
							}
						}
						if (find) {
							cout << "当前信息：" << endl;
							cout << s << endl;
							if (jur1 == 1) {
								cout << "输入新的数据：" << endl;
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								cin >> s;
								temp_file << s << "\n";
								temp_file.close();
								file.close();
								filesystem::remove("self_information.txt");
								filesystem::rename("temp_self_information.txt", "self_information.txt");
							}
							else if (jur1 == 2) {
								cout << "是否确定删除（1.确定 2.返回）" << endl;
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								cin >> jur3;
								while (true) {
									if (jur3 == 1) {
										temp_file.close();
										file.close();
										filesystem::remove("self_information.txt");
										filesystem::rename("temp_self_information.txt", "self_information.txt");
										cout << "删除成功" << endl;
										system("pause");
										break;
									}
									else if (jur3 == 2) {
										temp_file.close();
										file.close();
										filesystem::remove("temp_self_information.txt");
										system("pause");
										break;
									}
									else
										cout << "请输入合法数字" << endl;
								}
							}
						}
						else {
							cout << "未找到相关信息" << endl;
							file.close();
							temp_file.close();
							filesystem::remove("temp_self_information.txt");
							system("pause");
						}
					}
					else {
						cout << "请输入合法数字" << endl;
						system("pause");
					}
				}
			}
			case 5: {
				while (true) {
					system("cls");
					cout << "请输入要修改的专业（输入0退出）" << endl;
					bool find = false;
					string major, school_id, * subject, file_school_id;
					int number, * m, * score;
					cin >> major;
					if (major == "0")
						break;
					major += ".txt";
					fstream file(major, ios::in | ios::out);//打开该专业对应文件
					ofstream temp_file("temp.txt", ios::app);
					if (!file) {
						cout << "打开文件失败" << endl;
						system("pause");
						file.close();
						temp_file.close();
						filesystem::remove("temp.txt");
						break;
					}
					file >> number;//按格式读入文件内部科目信息
					temp_file << number << " ";
					subject = new string[number];
					m = new int[number];
					score = new int[number];
					for (int n = 0;n < number;n++) {
						file >> subject[n];
						temp_file << subject[n];
						if (n != number - 1)
							temp_file << " ";
						else
							temp_file << "\n";
					}
					system("cls");
					cout << "请输入想修改的学号" << endl;
					cin >> school_id;
					while (file >> file_school_id) {//检测文件内有无学号对应信息
						for (int n = 0;n < number;n++) {
							file >> m[n];
						}
						if (school_id == file_school_id) {
							find = true;
							for (int n = 0;n < number;n++) {
								score[n] = m[n];
							}
						}
						else {
							temp_file << file_school_id << " ";
							for (int n = 0;n < number;n++) {
								temp_file << m[n];
								if (n != number - 1)
									temp_file << " ";
								else
									temp_file << "\n";
							}
						}
					}
					if (find) {//如有该学号对应信息，选择修改类型，利用临时文件法实现信息的删除或更改
						system("cls");
						cout << "1.修改信息 2.删除信息 0.退出" << endl;
						int jur,jur1;
						cin >> jur;
						system("cls");
						cout << "当前信息为：" << endl;
						for (int n = 0;n < number;n++) {
							cout << subject[n];
							if (n != number - 1)
								cout << " ";
							else
								cout << "\n";
						}
						cout << school_id << " ";
						for (int n = 0;n < number;n++) {
							cout << score[n];
							if (n != number - 1)
								cout << " ";
							else
								cout << "\n";
						}
						if (jur == 1) {
							cout << "请输入更新的数据" << endl;
							cin >> school_id;
							for (int n = 0;n < number;n++) {
								cin >> score[n];
							}
							temp_file << school_id << " ";
							for (int n = 0;n < number;n++) {
								temp_file << score[n];
								if (n != number - 1)
									temp_file << " ";
								else
									temp_file << "\n";
							}
							cout << "更新完成" << endl;
							temp_file.close();
							file.close();
							filesystem::remove(major);
							filesystem::rename("temp.txt", major);
							system("pause");
						}
						else if (jur == 2) {
							cout << "1.确定删除 0.退出删除" << endl;
							cin >> jur1;
							if (jur1 == 1) {
								temp_file.close();
								file.close();
								filesystem::remove(major);
								filesystem::rename("temp.txt", major);
							}
							else if (jur1 == 0) {
								filesystem::remove("temp.txt");
								cout << "删除成功！" << endl;
								system("pause");
							}
							else {
								cout << "输入数字不合法！将返回上一界面" << endl;
								system("pause");
							}
						}
						else if (jur == 0);
						else {
							cout << "请输入合法的数字" << endl;
							system("pause");
						}
					}
					else {
						system("cls");
						cout << "未找到学号信息" << endl;
						temp_file.close();
						file.close();
						filesystem::remove("temp.txt");
						system("pause");
					}
				}
				break;
			}
			case 6: {
				while (true) {//与上面同理，利用临时文件法，先搜索该学号信息是否存在，再对信息根据选择进行修改
					system("cls");
					int id, file_id, file_num, num;
					string* file_subject = NULL, * subject = NULL;
					bool find = false;
					cout << "请输入想修改的学号（按0退出）" << endl;
					cin >> id;
					if (id == 0)
						break;
					fstream file("honour.txt", ios::in | ios::out);
					ofstream temp_file("temp_honour.txt", ios::app);
					if (!file.is_open() || !temp_file.is_open()) {
						cout << "无法打开文件！" << endl;
						system("pause");
						break;
					}
					while (file >> file_id) {
						file >> file_num;
						file_subject = new string[file_num];
						for (int n = 0;n < file_num;n++) {
							file >> file_subject[n];
						}
						if (id == file_id) {
							find = true;
							subject = new string[file_num];
							num = file_num;
							for (int n = 0;n < file_num;n++) {
								subject[n] = file_subject[n];
							}
						}
						else {
							temp_file << file_id << " " << file_num << " ";
							for (int n = 0;n < file_num;n++) {
								temp_file << file_subject[n];
								if (n != file_num - 1) {
									temp_file << " ";
								}
								else {
									temp_file << "\n";
								}
							}
						}
					}
					if (find) {
						system("cls");
						cout << "1.修改信息 2.删除信息 0.退出" << endl;
						int jur;
						cin >> jur;
						system("cls");
						cout << "当前信息为：" << endl;
						cout << id << " ";
						for (int n = 0;n < num;n++) {
							cout << subject[n];
							if (n != num - 1)
								cout << " ";
							else
								cout << "\n";
						}
						while (true) {
							if (jur == 1) {
								cout << "请输入更新的信息（学号+成就内容1+成就内容1+……）（按0结束）" << endl;
								cin >> id;
								if (id == 0)
									break;
								num = 0;
								vector<string> sub;
								string s;
								while (true) {
									cin >> s;
									if (s == "0")
										break;
									sub.push_back(s);
									num++;
								}
								temp_file << id << " " << num << " ";
								for (int n = 0;n < num;n++) {
									temp_file << sub[n];
									if (n != num - 1)
										temp_file << " ";
									else
										temp_file << "\n";
								}
								file.close();
								temp_file.close();
								filesystem::remove("honour.txt");
								filesystem::rename("temp_honour.txt", "honour.txt");
								break;
							}
							else if (jur == 2) {
								system("cls");
								cout << "1.确定删除 2.退出" << endl;
								file.close();
								temp_file.close();
								filesystem::remove("honour.txt");
								filesystem::rename("temp_honour.txt", "honour.txt");
								system("cls");
								cout << "已删除" << endl;
								system("pause");
								break;
							}
							else if (jur == 0) {
								file.close();
								temp_file.close();
								filesystem::remove("temp_honour.txt");
								break;
							}
							else {
								cout << "请输入合法的数字" << endl;
							}
						}
					}
					else {
						cout << "未找到学号信息！" << endl;
						file.close();
						temp_file.close();
						filesystem::remove("temp_honour.txt");
						system("pause");
					}
				}
				break;
			}
			case 0:
				control = true;
				break;
			default:
				cout << "输入数字错误！请输入合法的数字" << endl;
				system("pause");
				break;
			}
			if (control)
				break;
		}
	}

	void Information_Viewing() {
		while (true) {
			system("cls");
			int j;
			cout << "1.浏览个人信息 2.浏览成绩信息 3.浏览成就信息 0.退出" << endl;
			cin >> j;
			if (j == 1) {
				system("cls");
				cout << "1.查找个人信息 2.浏览所有信息 0.退出" << endl;
				int j1;
				cin >> j1;
				fstream file("self_information.txt", ios::in | ios::out);
				if (j1 == 1) {//利用map容器，按选择类型确定键，实现快捷搜索
					while (true) {
						system("cls");
						cout << "1.输入名字查找 2.输入学号查找 0.退出" << endl;
						int j2;
						cin >> j2;
						map<string, Student> stu;
						Student student;
						if (j2 == 1) {
							while (file >> student) {
								stu[student.Get_Name()] = student;
							}
							system("cls");
							cout << "请输入姓名" << endl;
							string name;
							cin >> name;
							auto it = stu.find(name);
							if (it == stu.end()) {
								cout << "未找到对应信息！" << endl;
								system("pause");
							}
							else {
								cout << it->second << endl;
								system("pause");
							}
							break;
						}
						else if (j2 == 2) {
							while (file >> student) {
								stu[student.Get_School_Id()] = student;
							}
							system("cls");
							cout << "请输入学号" << endl;
							string school_id;
							cin >> school_id;
							auto it = stu.find(school_id);
							if (it == stu.end()) {
								cout << "未找到对应信息！" << endl;
								system("pause");
							}
							else {
								cout << it->second << endl;
								system("pause");
							}
							break;
						}
						else if (j2 == 0) {
							break;
						}
						else {
							cout << "请输入合法的数字!" << endl;
							system("pause");
						}
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
				}
				else if (j1 == 2) {
					system("cls");
					Student student;
					while (file >> student) {
						cout << student << endl;
					}
					system("pause");
				}
				else if (j1 == 0) {
					break;
				}
				else {
					cout << "请输入合法的数字！" << endl;
					system("pause");
				}
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (j == 2) {
				system("cls");
				string major, subject, school_id;
				int subject_num,score;
				cout << "请输入浏览的专业" << endl;
				cin >> major;
				major += ".txt";
				fstream file(major, ios::in | ios::out);
				if (!file.is_open()) {
					cout << "无法打开文件！" << endl;
					system("pause");
					break;
				}
				system("cls");
				cout << "1.浏览全部信息 2.查找个人信息 0.退出" << endl;
				int j1;
				cin >> j1;
				system("cls");
				file >> subject_num;
				cout << "成绩依次为：" << endl;
				for (int n = 0;n < subject_num;n++) {
					file >> subject;
					cout << subject;
					if (n != subject_num - 1)
						cout << " ";
					else
						cout << "\n";
				}
				if (j1 == 1) {
					while (file >> school_id) {
						cout << school_id << " ";
						for (int n = 0;n < subject_num;n++) {
							file >> score;
							cout << score;
							if (n != subject_num - 1) {
								cout << " ";
							}
							else {
								cout << "\n";
							}
						}
					}
					system("pause");
				}
				else if (j1 == 2) {//读到指定学号后打印信息
					cout << "请输入学号" << endl;
					string id;
					bool find = false;
					cin >> id;
					while (file >> school_id) {
						if (school_id == id) {
							find = true;
							cout << id << " ";
							for (int n = 0;n < subject_num;n++) {
								file >> score;
								cout << score;
								if (n != subject_num - 1) {
									cout << " ";
								}
								else {
									cout << "\n";
								}
							}
							system("pause");
							break;
						}
						for (int n = 0;n < subject_num;n++) {
							file >> score;
						}
					}
					if (!find) {
						cout << "未找到相关信息！" << endl;
						system("pause");
					}
				}
				else if (j1 == 0);
				else {
					cout << "请输入合法的数字" << endl;
					system("pause");
				}
			}
			else if (j == 3) {
				system("cls");
				fstream file("honour.txt", ios::in | ios::out);
				if (!file.is_open()) {
					cout << "无法打开文件！" << endl;
					system("pause");
					break;
				}
				int file_id, id, file_num, num;
				cout << "1.浏览全部信息 2.查找个人信息 0.退出" << endl;
				int j;
				cin >> j;
				if (j == 1) {
					system("cls");
					string honour;
					while (file >> file_id) {
						cout << file_id << " ";
						file >> file_num;
						for (int n = 0;n < file_num;n++) {
							file >> honour;
							cout << honour;
							if (n != file_num - 1)
								cout << " ";
							else
								cout << "\n";
						}
					}
					system("pause");
				}
				else if (j == 2) {//与上一种同理，如果搜索到指定学号，就把对应信息打印出来
					system("cls");
					string honour;
					bool find = false;
					cout << "请输入查找的学号" << endl;
					cin >> id;
					while (file >> file_id) {
						file >> file_num;
						if (id == file_id) {
							cout << file_id << " ";
							for (int n = 0;n < file_num;n++) {
								file >> honour;
								cout << honour << " ";
								if (n != file_num - 1)
									cout << " ";
								else
									cout << "\n";
							}
							find = true;
							system("pause");
							break;
						}
						for (int n = 0;n < file_num;n++) {
							file >> honour;
						}
					}
					if (!find) {
						cout << "未找到该学号信息" << endl;
						system("pause");
					}
				}
				else if (j == 0);
				else {
					cout << "请输入合法的数字" << endl;
					system("pause");
				}
			}
			else if (j == 0) {
				break;
			}
			else {
				cout << "请输入合法数字" << endl;
				system("pause");
			}
		}
	}
};

class Student_manager {
public:
	void Run() {//首先使Menu指针指向Menu类型对象，调用构造函数选择用户类型后，指向对应对象，进行后续操作
		Menu* m=new Menu;
		if (m->Get_Type() == teacher) {
			delete m;
			m = new Teacher_menu;
		}
		else if (m->Get_Type() == student) {
			delete m;
			m = new Student_menu;
		}
		system("cls");
		m->Log_In();
		while (true) {
			system("cls");
			m->Menu_Show();
			int jur = 1;
			if (m->Get_Type() == teacher)
				cin >> jur;
			m->Fuction_Jump(jur);
			if (m->Get_log() == false)
				break;
		}
		cout << "程序已退出" << endl;
		system("pause");
	}
};
