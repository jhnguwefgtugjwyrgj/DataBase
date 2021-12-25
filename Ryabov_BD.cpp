#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

class Students {
	string fname;
	int col=0, row=0;
	vector <string> head;
	vector <vector <string> > mat;
	public:
		Students(string);
		void Close();
		void Insert();
		void Out();
		void Change(int n);
		vector <string> Choose(int n);
		void NewCol();
		vector<string> NewMark();
		int Getcol();
		int Getrow();
		string Getfio(int n);
		void Del(int n);
		void Cellcahnge(int i, int j, string s);
};

bool check(Students s, int n) {
    return (n <= s.Getrow() && n >= 1);
}

bool check_num(string s) {
    try {
        int a;
        a = stoi(s);
        return true;
    }
    catch (...) {
        return false;
    }
}

Students::Students(string name="students.txt") {
	ifstream Fin(name.c_str());
	fname = name;
	string s, cur="";
	int j=0;
	getline(Fin, s);
	if (s.size() == 0){
	    if (name=="students.txt") {
    		vector <string> h = {"familiya", "imya", "otchectvo"};
    		head = h;
    		col = head.size();
    	}
    	if (name=="subjects.txt") {
    		vector <string> h = {"subject"};
    		head = h;
    		col = head.size();
    	}
    	if (name=="marks.txt") {
    		vector <string> h = {"id_st", "id_sub", "mark"};
    		head = h;
    		col = head.size();
    	}
	}
	else {
		s = s.substr(0, s.size());
		for (size_t i=0;i<s.size();i++) {
			if (s[i] != ' ') cur += s[i];
			else {
				head.push_back(cur);
				cur="";
			}
		}
		head.push_back(cur);
		col = head.size();
		while (!Fin.eof()) {
			vector<string>r(col, "");
			for (size_t i=0;i<col;i++) {
				Fin >> r[i];
			}
			mat.push_back(r);
			row++;
		}
	}
	Fin.close();
}

void Students::Close() {
	ofstream Fout;
	Fout.open(fname.c_str());
	for (size_t i=0;i<col-1;i++) {
		Fout << head[i] << " ";
	}
	Fout << head[col-1];
	if (row > 0) Fout << endl;
	for (int i=0;i<row-1;i++) {
		for (int j=0;j<col;j++) {
			if (j != col-1) Fout << mat[i][j] << " ";
			else Fout << mat[i][j] << endl;
		}
	}
	if (row > 0) {
	    for (int j=0;j<col;j++) {
		    if (j != col-1) Fout << mat[row-1][j] << " ";
		    else Fout << mat[row-1][j];
	    }
	}
	Fout.close();
}

void Students::Insert() {
	vector <string> line(col);
	for (int i=0;i<col;i++) {
	    cout << "Print " << head[i] << ": ";
	    string t;
	    cin >> t;
	    line[i] = t;
	}
	mat.push_back(line);
	row++;
}

void Students::Out() {
    cout << "id ";
    for (int i=0;i<col;i++) {
        cout << head[i] << " ";
    }
    cout << endl;
    for (int i=0;i<row;i++) {
        cout << i+1 << " ";
        for (int j=0;j<col;j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void Students::Change(int n) {
    vector <string> line(col);
	for (int i=0;i<col;i++) {
	    cout << "Print " << head[i] << ": ";
	    string t;
	    cin >> t;
	    line[i] = t;
	}
	mat[n-1] = line;
}

vector <string> Students::Choose(int n) {
    return mat[n-1];
}

void Students::NewCol() {
    cout << "Print name column: ";
    string s;
    cin >> s;
    head.push_back(s);
    for (int i=0;i<row;i++) {
        mat[i].push_back("");
    }
    col++;
}

int Students::Getrow() {
    return row;
}

int Students::Getcol() {
    return col;
}

string Students::Getfio(int n) {
    return mat[n-1][0]+" "+mat[n-1][1]+" "+mat[n-1][2];
}

void Students::Del(int n) {
    mat.erase(mat.begin()+(n-1));
    row--;
}

vector <string> Students::NewMark() {
    vector <string> line(3);
    cout << "Print student id: ";
    cin >> line[0];
    cout << "Print subject id: ";
    cin >> line[1];
    cout << "Print mark: ";
    cin >> line[2];
    mat.push_back(line);
    row++;
    return line;
}

void Students::Cellcahnge(int i, int j, string s) {
    mat[i][j] = s;
}


int main() {
	Students pup("students.txt");
	Students sub("subjects.txt");
	Students mar("marks.txt");
	vector <vector <int> > ans(pup.Getrow(), vector<int>(sub.Getrow(), 0)), g(pup.Getrow(), vector<int>(sub.Getrow(), 0));
	//cout << ans.size() << " " << ans[0].size()<<endl;
	for (int i=0;i<mar.Getrow();i++) {
	    vector <string> e = mar.Choose(i+1);
	    //cout << e[0] << " " << e[1] << endl;
	    ans[stoi(e[0])-1][stoi(e[1])-1] += stoi(e[2]);
	    g[stoi(e[0])-1][stoi(e[1])-1]++;
	}
	vector <string> fio;
	for (int i=0;i<pup.Getrow();i++) {
	    fio.push_back(pup.Getfio(i+1));
	}
	vector <string> head_ans(1, "fio");
	for (int i=0;i<sub.Getrow();i++) {
	    head_ans.push_back(sub.Choose(i+1)[0]);
	}
	cout << "Welcome" << endl;
	cout << "Enter command (help for command list)" << endl;
	while (true) {
	    string com;
	    getline(cin, com);
	    if (com == "exit") {
	        break;
	    }
	    if (com == "add students string") {
	        pup.Insert();
	        string t = pup.Getfio(pup.Getrow());
            fio.push_back(t);
            ans.push_back(vector<int>(head_ans.size()-1, 0));
            g.push_back(vector<int>(head_ans.size()-1, 0));
	    }
	    if (com == "add students column") {
	        pup.NewCol();
	    }
	    if (com == "add mark") { 
	        vector <string> e = mar.NewMark();
	        if (check_num(e[0])&& check_num(e[1]) && check_num(e[2]) && check(pup, stoi(e[0])) && check(sub, stoi(e[1]))) {
	            //cout << stoi(e[0])-1 << " " << stoi(e[1])-1 << " " << ;
	            ans[stoi(e[0])-1][stoi(e[1])-1] += stoi(e[2]);
	            g[stoi(e[0])-1][stoi(e[1])-1]++;
	        }
	        else {
	            cout << "Uncorrect data\n";
	            mar.Del(mar.Getrow());
	        }
	    }
	    if (com == "add subject") {
	        sub.Insert();
	        head_ans.push_back(sub.Choose(sub.Getrow())[0]);
	        for (int i=0;i<ans.size();i++) {
	            ans[i].push_back(0);
	            g[i].push_back(0);
	        }
	    }
	    if (com == "change student") {
	        int k;
	        cin >> k;
	        if (check(pup, k)) {
	            pup.Change(k);
	            fio[k-1] = pup.Getfio(k);
	        }
	        else cout << "Wrong number\n";
	    }
	    if (com == "get request") {
	        ofstream Fout("request.txt");
	        for (int i=0;i<head_ans.size();i++) {
	            Fout << head_ans[i] << " ";
	        }
	        Fout << endl;
	        for (int i=0;i<ans.size();i++) {
	            Fout << fio[i] << " ";
	            for (int j=0;j<ans[i].size();j++) {
	                if (g[i][j] > 0) Fout << ans[i][j]/g[i][j] << " ";
	                else Fout << 0 << " ";
	            }
	            Fout << endl;
	        }
	        Fout.close();
	    }
	    if (com == "out subjects") {
	        sub.Out();
	    }
	    if (com == "out students") {
	        pup.Out();
	    }
	    if (com == "out marks") {
	        mar.Out();
	    }
	    if (com == "delete student") {
	        int t, i=0;
	        cin >> t;
	        if (check(pup, t)) {
	            pup.Del(t);
	            ans.erase(ans.begin()+(t-1));
	            g.erase(g.begin()+(t-1));
	            while (i<mar.Getrow()) {
	                vector <string> e = mar.Choose(i+1);
	                if (stoi(e[0]) == t) mar.Del(i+1);
	                else if (stoi(e[0])>t) mar.Cellcahnge(i, 0, to_string(stoi(e[0])-1));
	                i++;
	            }
	        }
	        else cout << "Wrong number\n";
	    }
	    if (com == "help") {
			cout << "command list:\nadd students column - adds column for students table\n" <<
			"add students string - adds new student\n" <<
			"add mark - adds a grade for a student(id) by subject(id)\n" <<
			"add subject - adds subject\n" <<
			"change student - changes data for a student with some id\n" <<
			"out subjects/students/marks - output information about subjects/students/marks\n" <<
			"delete student - delete student with some id and his marks\n" <<
			"get request - creates a file with average grades for students\n" <<
			"exit - ends the program\n";
		}
	}
	sub.Close();
	mar.Close();
	pup.Close();
	return 0;
} 

