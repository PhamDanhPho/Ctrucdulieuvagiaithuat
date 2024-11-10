#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class NhanVien {
private:
    int maNV;
    string hoTen;
    string gioiTinh;
    int tuoi;
    string viTri;    
    float luongTheoGio;
    int soGioLam; 

public:
    NhanVien() : maNV(0), hoTen(""), gioiTinh(""), tuoi(0), viTri(""), luongTheoGio(0), soGioLam(0) {}

    friend istream& operator>>(istream& is, NhanVien& nv) {
        cout << "Nhap ma nhan vien: ";
        is >> nv.maNV;
        is.ignore();
        cout << "Nhap ho ten nhan vien: ";
        getline(is, nv.hoTen);
        cout << "Nhap gioi tinh (Nam/Nu): ";
        getline(is, nv.gioiTinh);
        cout << "Nhap tuoi nhan vien: ";
        is >> nv.tuoi;
        is.ignore();
        cout << "Nhap vi tri lam (Bep, Phuc Vu, To Truong): ";
        getline(is, nv.viTri);
        cout << "Nhap luong theo gio: ";
        is >> nv.luongTheoGio;
        cout << "Nhap so gio lam trong thang: ";
        is >> nv.soGioLam;
        return is;
    }

    friend ostream& operator<<(ostream& os, const NhanVien& nv) {
        os << "Ma NV: " << nv.maNV << ", Ho Ten: " << nv.hoTen << ", Gioi Tinh: " << nv.gioiTinh
           << ", Tuoi: " << nv.tuoi << ", Vi Tri: " << nv.viTri << ", Luong theo gio: " << nv.luongTheoGio
           << ", So gio lam: " << nv.soGioLam;
        return os;
    }

    bool operator<(const NhanVien& nv) const {
        return maNV < nv.maNV;
    }

    int getMaNV() const { return maNV; }
    float tinhLuong() const { return luongTheoGio * soGioLam; }
};

class QuanLyNhanVien {
private:
    vector<NhanVien> danhSachNV;

public:
    void themNhanVien(const NhanVien& nv) {
        danhSachNV.push_back(nv);
    }

    void xoaNhanVien(int maNV) {
        bool found = false;
        for (size_t i = 0; i < danhSachNV.size(); i++) {
            if (danhSachNV[i].getMaNV() == maNV) {
                danhSachNV.erase(danhSachNV.begin() + i);
                cout << "Nhan vien voi ma " << maNV << " da bi xoa.\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Khong tim thay nhan vien voi ma " << maNV << " de xoa.\n";
        }
    }

    void hienThiDanhSachNV() const {
        for (vector<NhanVien>::const_iterator it = danhSachNV.begin(); it != danhSachNV.end(); ++it) {
            cout << *it << endl;
        }
    }

    void timKiemNhanVien(int maNV) const {
        bool found = false;
        for (vector<NhanVien>::const_iterator it = danhSachNV.begin(); it != danhSachNV.end(); ++it) {
            if (it->getMaNV() == maNV) {
                cout << "Nhan vien tim thay: " << *it << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Khong tim thay nhan vien voi ma " << maNV << endl;
        }
    }

    void sapXepNhanVien() {
        sort(danhSachNV.begin(), danhSachNV.end());
        cout << "Danh sach nhan vien da duoc sap xep theo ma NV.\n";
    }

    void tinhLuongNhanVien() const {
        for (vector<NhanVien>::const_iterator it = danhSachNV.begin(); it != danhSachNV.end(); ++it) {
            cout << "Luong cua nhan vien " << it->getMaNV() << " la: " << it->tinhLuong() << ".000.000 VND.\n";
        }
    }
};

class App {
private:
    QuanLyNhanVien qlNhanVien;

public:
    void hienThiMenu() {
        int choice;
        char cont;
        
        do {
            cout << "\n--- Quan Ly Nhan Vien ---\n";
            cout << "1. Nhap danh sach nhan vien\n";
            cout << "2. Xoa nhan vien\n";
            cout << "3. Sap xep danh sach nhan vien theo ma NV\n";
            cout << "4. Hien thi danh sach nhan vien\n";
            cout << "5. Tim kiem nhan vien\n";
            cout << "6. Tinh luong nhan vien\n";
            cout << "7. Thoat\n";
            cout << "Nhap lua chon cua ban: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    do {
                        NhanVien nv;
                        cin >> nv;
                        qlNhanVien.themNhanVien(nv);
                        cout << "Ban co muon nhap tiep khong (c/k)? ";
                        cin >> cont;
                    } while (cont == 'c' || cont == 'C');
                    break;
                }
                case 2: {
                    int maNV;
                    cout << "Nhap ma nhan vien can xoa: ";
                    cin >> maNV;
                    qlNhanVien.xoaNhanVien(maNV);
                    break;
                }
                case 3:
                    qlNhanVien.sapXepNhanVien();
                    break;
                case 4:
                    qlNhanVien.hienThiDanhSachNV();
                    break;
                case 5: {
                    int maNV;
                    cout << "Nhap ma nhan vien can tim: ";
                    cin >> maNV;
                    qlNhanVien.timKiemNhanVien(maNV);
                    break;
                }
                case 6:
                    qlNhanVien.tinhLuongNhanVien();
                    break;
                case 7:
                    cout << "Thoat chuong trinh.\n";
                    break;
                default:
                    cout << "Lua chon khong hop le.\n";
            }
        } while (choice != 7);
    }
};

int main() {
    App app;
    app.hienThiMenu();
    return 0;
}
