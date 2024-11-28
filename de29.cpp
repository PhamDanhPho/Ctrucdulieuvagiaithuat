#include <iostream>
#include <string>
using namespace std;
class CV {
public:
    int startHour;
    string tenCV;
    string content;
    string level;
    bool completed;
    CV* next;
    
    CV(int hour, string name, string nd, string md, bool done) {
        startHour = hour;
        tenCV = name;
        content = nd;
        level = md;
        completed = done;
        next = NULL;
    }
};
class DayNode {
public:
    int day;
    CV* dsCV;
    DayNode* left;
    DayNode* right;

    DayNode(int d) {
        day = d;
        dsCV = NULL;
        left = NULL;
        right = NULL;
    }
    void themCV(int hour, string name, string nd, string md, bool completed) {
        CV* newTask = new CV(hour, name, nd, md, completed);
        if (!dsCV || dsCV->startHour > hour) {
            newTask->next = dsCV;
            dsCV = newTask;
        } else {
            CV* current = dsCV;
            while (current->next && current->next->startHour < hour) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
    }
    void hienthiCV() {
        CV* current = dsCV;
        while (current) {
            cout << "Hour: " << current->startHour << ", Task: " << current->tenCV
                 << ", Level: " << current->level
                 << ", Completed: " << (current->completed ? "Yes" : "No") << endl;
            current = current->next;
        }
    }
};
class BST {
public:
    DayNode* root;
    BST() {
        root = NULL;
    }
    DayNode* addDay(DayNode* node, int day) {
        if (!node) {
            return new DayNode(day);
        }
        if (day < node->day) {
            node->left = addDay(node->left, day);
        } else if (day > node->day) {
            node->right = addDay(node->right, day);
        }
        return node;
    }
    void themCV(int day, int hour, string name, string nd, string md, string completedStr) {
        root = addDay(root, day);
        DayNode* dayNode = findDay(root, day);
        if (dayNode) {
        	bool completed = (completedStr == "hoan thanh");
            dayNode->themCV(hour, name, nd, md, completed);
        }
    }
    DayNode* findDay(DayNode* node, int day) {
        if (!node || node->day == day) {
            return node;
        }
        if (day < node->day) {
            return findDay(node->left, day);
        }
        return findDay(node->right, day);
    }
    void xemCVtheongay(int day) {
        DayNode* dayNode = findDay(root, day);
        if (dayNode) {
            cout << "CV trong ngay " << day << ":" << endl;
            dayNode->hienthiCV();
        } else {
            cout << "Khong co CV trong ngay " << day << endl;
        }
    }
    void xemCVtheotinhchat(DayNode* node, string priority, bool &found) {
    if (!node) return;
    xemCVtheotinhchat(node->left, priority, found);

    CV* current = node->dsCV;
    while (current) {
        if (current->level == priority) {
            if (!found) {
                cout << "CV co muc do uu tien: " << priority << endl;
                found = true;
            }
            cout << "Day: " << node->day << " | Hour: " << current->startHour 
                 << " | Name: " << current->tenCV << " | Level: " << current->level << endl;
        }
        current = current->next;
    }
    xemCVtheotinhchat(node->right, priority, found);
	}
	void xemCVtheotinhchat(string priority) {
    	bool found = false;
    	xemCVtheotinhchat(root, priority, found);
    	if (!found) { 
        	cout << "Khong co cong viec nao cho muc do uu tien " << priority << endl;
    	}
	}
    void xemCVdahoanthanh(DayNode* node, bool &found) {
        if (!node) return;
        xemCVdahoanthanh(node->left, found);
        CV* current = node->dsCV;
        while (current) {
            if (current->completed) {
            	if(!found){
            		cout << "Cac CV da hoan thanh: " << endl;
            		found = true;
				}
                cout << "Day: " << node->day << " | Hour: " << current->startHour 
                     << " | Name: " << current->tenCV << " | Completed: Yes" << endl;
            }
            current = current->next;
        }
        xemCVdahoanthanh(node->right, found);
    }
    void xemCVdahoanthanh() {
    	bool found = false;
        xemCVdahoanthanh(root, found);
        if (!found) { 
        	cout << "Khong co cong viec nao da hoan thanh! " << endl;
    	}
    }
    void xemCVchuathuchien(DayNode* node, bool &found) {
        if (!node) return;
        xemCVchuathuchien(node->left, found);
        CV* current = node->dsCV;
        while (current) {
            if (!current->completed) {
            	if(!found){
            		cout << "CV dang cho xu ly:" << endl;
            		found = true;
				}
                cout << "Day: " << node->day << " | Hour: " << current->startHour 
                     << " | Name: " << current->tenCV << " | Completed: No" << endl;
            }
            current = current->next;
        }
        xemCVchuathuchien(node->right, found);
    }
    void xemCVchuathuchien() {
        bool found = false;
        xemCVchuathuchien(root, found);
        if (!found) { 
        	cout << "Khong co cong viec nao chua thuc hien! " << endl;
    	}
    }
    void xemCVtungayadenb(DayNode* node, int startDay, int endDay) {
        if (!node) return;
        if (node->day >= startDay) {
            xemCVtungayadenb(node->left, startDay, endDay);
        }
        if (node->day >= startDay && node->day <= endDay) {
            cout << "CV cua ngay " << node->day << ":" << endl;
            node->hienthiCV();
        }
        if (node->day <= endDay) {
            xemCVtungayadenb(node->right, startDay, endDay);
        }
    }
    void xemCVtungayadenb(int startDay, int endDay) {
        cout << "CV tu ngay " << startDay << " toi ngay " << endDay << ":" << endl;
        xemCVtungayadenb(root, startDay, endDay);
    }
    void xoaCV(DayNode* dayNode, int hour) {
        CV* current = dayNode->dsCV;
        CV* prev = NULL;
        while (current && current->startHour != hour) {
            prev = current;
            current = current->next;
        }
        if (!current) {
            cout << "CV cua gio " << hour << " khong tim thay." << endl;
            return;
        }
        if (prev) {
            prev->next = current->next;
        } else {
            dayNode->dsCV = current->next;
        }
        delete current;
        cout << "CV cua gio " << hour << " da bi xoa." << endl;
    }
    void xoaCV(int day, int hour) {
        DayNode* dayNode = findDay(root, day);
        if (!dayNode) {
            cout << "Ngay " << day << " khong tim thay." << endl;
            return;
        }
        xoaCV(dayNode, hour);
        if (!dayNode->dsCV) {
            root = deleteDay(root, day);
            cout << "Ngay " << day << " da bi xoa vi khong con CV nao." << endl;
        }
    }
    DayNode* deleteDay(DayNode* node, int day) {
        if (!node) return NULL;
        if (day < node->day) {
            node->left = deleteDay(node->left, day);
        } else if (day > node->day) {
            node->right = deleteDay(node->right, day);
        } else {
            if (!node->left) {
                DayNode* rightChild = node->right;
                delete node;
                return rightChild;
            } else if (!node->right) {
                DayNode* leftChild = node->left;
                delete node;
                return leftChild;
            }
            DayNode* minRight = node->right;
            while (minRight->left) {
                minRight = minRight->left;
            }
            node->day = minRight->day;
            node->dsCV = minRight->dsCV;
            node->right = deleteDay(node->right, minRight->day);
        }
        return node;
    }
};
int main() {
    BST schedule;
    int choice;

    do {
        cout << "\n--- Task Management System ---\n";
        cout << "1. Nhap cong viec\n";
        cout << "2. Xem cong viec theo ngay\n";
        cout << "3. Xem cong viec theo muc do uu tien\n";
        cout << "4. Xem cac cong viec da hoan tat\n";
        cout << "5. Xem cac cong viec chua thuc hien\n";
        cout << "6. Xem cong viec tu ngay A den ngay B\n";
        cout << "7. Xoa cong viec\n";
        cout << "8. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int day, hour, numTasks;
            string taskName, taskContent, priority, completed;

            cout << "Nhap so cong viec muon them: ";
            cin >> numTasks;

            for (int i = 0; i < numTasks; i++) {
                cout << "Nhap ngay: ";
                cin >> day;
                cout << "Nhap gio (0-23): ";
                cin >> hour;
                cin.ignore();
                cout << "Nhap ten cong viec: ";
                getline(cin, taskName);
                cout << "Nhap noi dung cong viec: ";
                getline(cin, taskContent);
                cout << "Nhap muc do uu tien (rat quan trong, quan trong, binh thuong, khong can thiet): ";
                getline(cin, priority);
				cout<< "Trang thai cong viec(nhap 'hoan thanh' neu CV da hoan thanh): ";
				getline(cin, completed);
                schedule.themCV(day, hour, taskName, taskContent, priority, completed);
            }
            break;
        }
        case 2: { 
            int day;
            cout << "Nhap ngay de xem cong viec: ";
            cin >> day;
            schedule.xemCVtheongay(day);
            break;
        }
        case 3: { 
            string priority;
            cin.ignore(); 
            cout << "Nhap muc do uu tien (rat quan trong, quan trong, binh thuong, khong can thiet): ";
            getline(cin, priority);
            schedule.xemCVtheotinhchat(priority);
            break;
        }
        case 4: { 
            schedule.xemCVdahoanthanh();
            break;
        }
        case 5: { 
            schedule.xemCVchuathuchien();
            break;
        }
        case 6: { 
            int startDay, endDay;
            cout << "Nhap ngay bat dau: ";
            cin >> startDay;
            cout << "Nhap ngay ket thuc: ";
            cin >> endDay;
            schedule.xemCVtungayadenb(startDay, endDay);
            break;
        }
        case 7: { 
            int day, hour;
            cout << "Nhap ngay cua cong viec can xoa: ";
            cin >> day;
            cout << "Nhap gio bat dau cua cong viec can xoa: ";
            cin >> hour;
            schedule.xoaCV(day, hour);
            break;
        }
        case 8: {
            cout << "Ket thuc chuong trinh.\n";
            break;
        }
        default:
            cout << "Lua chon khong hop le!\n";
            break;
        }
    } while (choice != 8);
    return 0;
}
