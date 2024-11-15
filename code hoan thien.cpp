#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <sstream>
#include <cctype>

using namespace std;

// Cau truc de luu thong tin sinh vien
struct SinhVien {
    string STT; // So thu tu
    string MSSV; // Ma so sinh vien
    bool kiemTraChiChuCai;
	string Hovaten; // Ho va ten
    string Lop; // Lop
    string Quequan; // Que quan 
    string HocLuc; // Hoc Luc
    string Ngaybatdau; // Ngay bat dau o KTX
    string NhapNgayThangNam;
	string Hoancanh; // Hoan Canh
	bool LaMienGiam; // Chi tieu mien giam tien phong
    SinhVien* Next; // Con tro den sinh vien tiep theo
};


// Cau truc du luu thong tin phong
struct Phong {
    string STT; // So thu tu
    string IdPhong; // ID phong
    bool Codayducosovatchat; // Co day du co so vat chat khong
    SinhVien* Danhsachsinhvien; // Danh sach sinh vien trong phong
    double Chiphidien; // Chi phi dien
    double Chiphinuoc; // Chi phi nuoc
    double TongTienDienNuoc; // Tong chi phi dien nuoc
    bool PhongSach; // Tieu chi sach
    bool PhongDep; // Tieu chi dep
    bool PhongAnToan; // Tieu chi gon gang
    string GiaiThuongPhong; // Giai thuong phong
    Phong* Next; // Con tro den phong tiep theo
};

bool laNamNhuan(int nam) {
    if ((nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0) {
        return true;
    } else {
        return false;
    }
}

// Ham Nhap Thong Tin Sinh Vien
string NhapNgayThangNam() {
    int day, month, year;
    char sep1, sep2;
    while (true){
    cin >> day >> sep1 >> month >> sep2 >> year;
    if (cin.fail()) {
            cout << "Loi: Vui long chi nhap so theo dinh dang dd/mm/yyyy.\n";
            cin.clear();  // Xoa trang thai loi
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Bo qua cac ki tu khong hop le
            continue;  // Yeu cau nguoi dung nhap lai
        }
    // Kiem tra dau phan cach va tinh hop li cua pham vi ngay 
    if (sep1 != '/' || sep2 != '/' || day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2024) {
        cout << "Ngay thang khong hop le. Vui long nhap lai theo dinh dang (dd/mm/yyyy).\n";
        return NhapNgayThangNam();  // Lenh goi de quy de nhap lai
    }
    if (laNamNhuan (year)) {
    	if (day > 29 && month == 2){
    		 cout << "Ngay thang khong hop le. Vui long nhap lai theo dinh dang (dd/mm/yyyy).\n";
        return NhapNgayThangNam();  // Lenh goi de quy de nhap lai
		}
	}else{
		if (day > 28 && month == 2){
			cout << "Ngay thang khong hop le. Vui long nhap lai theo dinh dang (dd/mm/yyyy).\n";
        return NhapNgayThangNam();  // Lenh goi de quy de nhap lai
		}
	}
    // Dinh dang ngay duoi dang chuoi trong "dd/mm/yyyy"
    stringstream ss;
    ss << setw(2) << setfill('0') << day << "/"
       << setw(2) << setfill('0') << month << "/"
       << year;
    return ss.str();
}
}
    
// Ham kiem tra xem chuoi co chi chua ky tu chu cai hay khong
bool kiemTraChiChuCai(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && c != ' ') { // Kiem tra tung ky tu
            return false; // Neu co ky tu khong phai chu cai hoac khong phai khoang trang, tra ve false
        }
    }
    return true; // Tat ca ky tu deu la chu cai hoac khoang trang
}

// Ham them sinh vien vao danh sach
void ThemSinhVienTaiViTri(SinhVien*& Head, const SinhVien& SinhVienmoi, int viTri) {
    SinhVien* Nodemoi = new SinhVien(SinhVienmoi);
    Nodemoi->Next = NULL;

    if (viTri == 0) {
        // Them vao dau danh sach
        Nodemoi->Next = Head;
        Head = Nodemoi;
    } else {
        SinhVien* Current = Head;
        for (int i = 1; i < viTri - 1 && Current != NULL; i++) {
            Current = Current->Next; // Di chuyen den vi tri truoc vi tri chen
        }
        if (Current != NULL) {
            Nodemoi->Next = Current->Next; // Gan con tro tiep theo cua node moi
            Current->Next = Nodemoi; // Chen node moi vao danh sach
        } else {
            cout << "Vi tri khong hop li!" << endl;
            delete Nodemoi; // Xaa node moi neu khong chen duoc
            return;
        }
    }
}

// Ham xoa sinh vien toi vi tri
void XoaSinhVienTaiViTri(SinhVien*& Head, int viTri) {
    if (Head == NULL) {
        cout << "Danh sach rong!" << endl;
        return;
    }

      SinhVien* Current = Head;

    if (viTri == 0) {
        // Xoa node dau
        Head = Current->Next;
        delete Current;
        return;
    }

    for (int i = 1; i < viTri - 1 && Current != NULL; i++) {
        Current = Current->Next; // Di chuyen den vi tri truoc vi tri can xoa
    }

    if (Current == NULL || Current->Next == NULL) {
        cout << "Vi tri khong hop le!" << endl;
        return;
    }

    SinhVien* Temp = Current->Next; // Node can xoa
    Current->Next = Temp->Next; // Bo qua node can xoa
    delete Temp; // Giai phong bo nho
}

// Ham them phong vao danh sach
void ThemPhong(Phong*& Head, const Phong& Phongmoi) {
    Phong* Nodemoi = new Phong(Phongmoi);
    Nodemoi->Next = Head;
    Nodemoi->Danhsachsinhvien = NULL; Head = Nodemoi;
}

// Ham nhap thong tin sinh vien
void nhapSinhVien(SinhVien*& head) {
    SinhVien sinhVienMoi;

    cout << "Nhap thong tin sinh vien:" << endl;

    // Nhap MSSV
    while (true) {
        cout << "| MSSV: ";
        cin >> sinhVienMoi.MSSV;
        cin.ignore(); // Xoa bo dem de tranh loi getline sau do

        // Kiem tra MSSV da ton tai trong danh sach chua
        SinhVien* Current = head;
        bool exists = false;
        while (Current != NULL) {
            if (Current->MSSV == sinhVienMoi.MSSV) {
                exists = true; // MSSV da ton tai
                break;
            }
            Current = Current->Next;
        }

        // Neu MSSV da ton tai, yeu cau nhap lai
        if (exists) {
            cout << "MSSV da ton tai! Vui long nhap MSSV khac." << endl;
            continue; // Quay lai vong lap de nhap lai MSSV
        }

        // Kiem tra do dai va xem co phai la 10 ki tu hay khong
        if (sinhVienMoi.MSSV.length() == 10) {
            bool isAllDigits = true;
            bool hasLetter = false;

            for (size_t i = 0; i < sinhVienMoi.MSSV.length(); ++i) {
                char c = sinhVienMoi.MSSV[i];
                if (isdigit(c)) {
                    continue; // Neu la so, tiep tuc
                } else if (isalpha(c)) {
                    hasLetter = true; // Neu la chu cai, danh dau
                } else {
                    isAllDigits = false; // Neu khong phai so va khong phai chu cai, khong hop le
                    break;
                }
            }

            // Kiem tra dieu kien hop le
            if (isAllDigits || (hasLetter && sinhVienMoi.MSSV.length() == 10)) {
                break; // Neu la 10 so hoac 9 so va 1 chu, thoat khoi vong lap
            }
        }

        cout << "MSSV khong hop le. Vui long nhap lai (10 ki tu)." << endl;
    }

    // Nhap ho va ten
    while (true) {
        cout << "| Ho va ten: ";
        getline(cin, sinhVienMoi.Hovaten); // Nhap ho va ten

        // Kiem tra xem ho va ten co hop le khong
        if (!sinhVienMoi.Hovaten.empty() && kiemTraChiChuCai(sinhVienMoi.Hovaten)) {
            break; // Neu hop le, thoat khoi vong lap
        } else {
            cout << "Ho va ten khong hop le. Vui long nhap lai." << endl; // Thong bao loi
        }
    }

     
    // Nhap lop
    while (true) {
        cout << "| Lop: ";
        getline(cin, sinhVienMoi.Lop);
        if (!sinhVienMoi.Lop.empty()) {
            break; // Neu lop khong trong, thoat khoi vong lap
        }
        cout << "Lop khong duoc de trong. Vui long nhap lai." << endl;
    }

    // Nhap Que quan
    
    while (true) {
        cout << "| Que quan: ";
        getline(cin, sinhVienMoi.Quequan);
        
        // Kiem tra xem que quan co rong khong
        if (!sinhVienMoi.Quequan.empty()) {
            bool isValid = true;
            for (size_t i = 0; i < sinhVienMoi.Quequan.length(); ++i) {
                char c = sinhVienMoi.Quequan[i];
                if (!isalpha(c) && c != ' ') { // Chi cho phep ky tu chu va khoang trang
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                break; // Neu que quan hop le, thoat khoi vong lap
            }
        }
        
        cout << "Que quan khong duoc de trong va phai la ki tu chu. Vui long nhap lai." << endl;
    }
    
    // Nhap hoc luc
    while (true) {
        cout << "| Hoc luc (xuat sac/gioi/khac): ";
        getline(cin, sinhVienMoi.HocLuc);
        if (!sinhVienMoi.HocLuc.empty()) {
            break; // Neu hoc luc khong trong, thoat khoi vong lap
 }
        cout << "Hoc luc de trong. Vui long nhap lai: " << endl;
    }
    
    // Nhap ngay bat dau
     cout << "| Ngay Bat Dau o (dd/mm/yyyy): ";
    sinhVienMoi.Ngaybatdau = NhapNgayThangNam(); 
    getline(cin, sinhVienMoi.NhapNgayThangNam);

    // Nhap hoan canh
    while (true) {
        cout << "| Hoan canh (ho ngheo/mo coi/binh thuong): ";
        getline(cin, sinhVienMoi.Hoancanh);
        if (!sinhVienMoi.Hoancanh.empty()) {
            break; // Neu hoan canh khong rong, thoat khoi vong lap
        }
        cout << "Hoan canh de trong. Vui long nhap lai: " << endl;
    }

    // Kiem tra xem sinh vien co duoc mien giam hay khong
     sinhVienMoi.LaMienGiam = (sinhVienMoi.Hoancanh == "mo coi" || sinhVienMoi.Hoancanh == "ho ngheo") && (sinhVienMoi.HocLuc == "xuat sac");

    sinhVienMoi.Next = NULL; // Khoi tao con tro tiep theo
    ThemSinhVienTaiViTri(head, sinhVienMoi, 0); // Chen vao danh sach tai vi tri dau tien
}

// Ham nhap thong tin phong
void NhapPhong(Phong*& Head) {
    Phong PhongMoi;

    cout << "Nhap Thong Tin Phong:" << endl;

    
    
    // Kiem tra ID phong khong trung
    while (true) {
    cout << "| ID Phong: ";
    cin >> PhongMoi.IdPhong;
    cin.ignore();

    // Kiem tra xem ID phong da ton tai trong danh sach chua
    Phong* Current = Head;
    bool exists = false;
    while (Current != NULL) {
        if (Current->IdPhong == PhongMoi.IdPhong) {
            exists = true; // ID phong da ton tai
            break;
        }
        Current = Current->Next;
    }

    if (exists) {
        cout << "ID Phong da ton tai! Vui long nhap ID khac." << endl;
    } else {
        break; // ID phong hop le, thoat vong lap
    }
  }

    char CoSoVatChat;
    string input;
    while (true) {
    cout << "| Phong Co Day Du Co So Vat Chat Khong? (y/n): ";
    cin >> input;

    // Kiem tra do dai cua dau vao
    if (input.length() != 1 || (input[0] != 'y' && input[0] != 'Y' && input[0] != 'n' && input[0] != 'N')) {
        cout << "Nhap sai. Vui long nhap 'y' hoac 'n'." << endl;
        cin.clear(); // Xoa trang thai loi
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bo qua dong nhap
    } else {
        // Neu dau vao hop le, gan gia tri cho PhongMoi.Codayducosovatchat
        PhongMoi.Codayducosovatchat = (input[0] == 'y' || input[0] == 'Y');
        break; // Thoat vong lap
    }
  }
  
   // Nhap so luong ky dien
     double SoKiDien;

    do {
        cout << "| Nhap so luong ki dien: ";
        cin >> SoKiDien;

        // Kiem tra neu viec nhap lieu gap loi (tuc la khong phai so)
        if (cin.fail()) {
            cout << "Nhap sai ban phai nhap mot so. Vui long thu lai" << endl;
            cin.clear(); // Xóa trang thai loi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bo qua cac ki tu khong hop le 
        } else if (SoKiDien < 0) {
            cout << "So ki dien dang am. Vui long thu lai: " << endl; 
        } else {
            break; // Thoat khoi vang lap neu nhap dung
        }
    }while (true);

    PhongMoi.Chiphidien = SoKiDien * 2000; // Tinh chi phi dien

    // Nhap so luong khoi nuoc
    double soKhoiNuoc;

    do {
        cout << "| Nhap so luong khoi nuoc: ";
        cin >> soKhoiNuoc;

        // Kiem tra neu viec nhap lieu gap lai (tuc là khong phai so)
        if (cin.fail()) {
            cout << "Nhap sai ban phai nhap mot so. Vui long thu lai: " << endl;
            cin.clear(); // Xoa trang thai loi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bo qua cac ki tu khong hop le?
        } else if (soKhoiNuoc < 0) {
            cout << "so khoi nuoc dang am. Vui long thu lai: "<< endl;
        } else {
            break; // Thoat khoi vong lap nau nhap dung
        }
       }while (true);

    PhongMoi.Chiphinuoc = soKhoiNuoc * 8000; // Tinh chi phi nuoc
    // Tinh tong chi phi dien va nuoc
    PhongMoi.TongTienDienNuoc = PhongMoi.Chiphidien + PhongMoi.Chiphinuoc; // Tinh tong chi phi dien nuoc
      
    // Giai thuong phong
    char PhongSach, PhongDep, PhongAnToan;
    
    while (true) {
    cout << "| Tieu chi phong sach se (y/n): ";
    string input; // Su dung string de kiem tra do dai
    cin >> input;

    // Kiem tra do dai cua dau vao
    if (input.length() == 1) {
        PhongSach = input[0]; // Lay ky tu dau tien
        if (PhongSach == 'y' || PhongSach == 'Y') {
            PhongMoi.PhongSach = true;
            break;
        } else if (PhongSach == 'n' || PhongSach == 'N') {
            PhongMoi.PhongSach = false;
            break;
        }
    }
    cout << "Nhap sai. Vui long nhap 'y' hoac 'n'." << endl;
   }

    while (true) {
    cout << "| Tieu chi phong dep (y/n): ";
    string input; // Su dung string de kiem tra do dai
    cin >> input;

    // Kiem tra do dai cua dau vao
    if (input.length() == 1) {
        PhongDep = input[0]; // Lay ky tu dau tien
        if (PhongDep == 'y' || PhongDep == 'Y') {
            PhongMoi.PhongDep = true;
            break;
        } else if (PhongDep == 'n' || PhongDep == 'N') {
            PhongMoi.PhongDep = false;
            break;
        }
    }
    cout << "Nhap sai. Vui long nhap 'y' hoac 'n'." << endl;
    }

    while (true) {
    cout << "| Tieu chi phong an toan (y/n): ";
    string input; // Su dung string de kiem tra do dai
    cin >> input;

    // Kiem tra do dai cua dau vao
    if (input.length() == 1) {
        PhongAnToan = input[0]; // Lay ky tu dau tien
        if (PhongAnToan == 'y' || PhongAnToan == 'Y') {
            PhongMoi.PhongAnToan = true;
            break;
        } else if (PhongAnToan == 'n' || PhongAnToan == 'N') {
            PhongMoi.PhongAnToan = false;
            break;
        }
    }
    cout << "Nhap sai. Vui long nhap 'y' hoac 'n'." << endl;
}

// Kiem tra so tieu chi dat duoc
   int tieuChiDatDuoc = 0;

    if (PhongMoi.PhongSach) {
    tieuChiDatDuoc++;
   }
   if (PhongMoi.PhongDep) {
    tieuChiDatDuoc++;
    }
    if (PhongMoi.PhongAnToan) {
    tieuChiDatDuoc++;
    }

    // Xac dinh giai thuong
    if (tieuChiDatDuoc == 3) {
    PhongMoi.GiaiThuongPhong = "Giai Nhat"; // Gan giai thuong cho phong
    } else if (tieuChiDatDuoc == 2) {
    PhongMoi.GiaiThuongPhong = "Giai Khuyen Khich"; // Gan giai thuong cho phong
    } else {
    PhongMoi.GiaiThuongPhong = "Khong Dat Giai"; // Gan giai thuong cho phong
    }

    PhongMoi.Danhsachsinhvien = NULL; // Khoi tao danh sach sinh vien rong
    PhongMoi.Next = NULL; // Khoi tao con tro tiep theo
    ThemPhong(Head, PhongMoi);
}

// Ham in danh sach sinh vien
void InDanhSachSinhVien(SinhVien* Head) {
    cout << "=============================================================================================================================================" << endl;
    cout << " | " << setw(3)  << "STT" 
         << " | " << setw(9)  <<  "MSSV" 
         << " | " << setw(25) <<  "Ho Va Ten" 
         << " | " << setw(11) <<  "Lop" 
         << " | " << setw(14) <<  "Que Quan" 
         << " | " << setw(11) <<  "Hoc Luc" 
         << " | " << setw(15) <<  "Ngay Bat Dau"
         << " | " << setw(12) <<  "Hoan Canh"
         << " | " << setw(10) <<  "Mien Giam"
         << " |"     << endl;
    cout << "=============================================================================================================================================" << endl;

    SinhVien* Current = Head;
    int index = 1; // Bien de dem so thu tu
    while (Current != NULL) {
        cout << " | " 
             << setw(3)   << index // In so thu tu
             << " | " 
             << setw(9)  << Current->MSSV 
             << " | " 
             << setw(25) << Current->Hovaten 
             << " | " 
             << setw(11) << Current->Lop 
             << " | " 
             << setw(14) << Current->Quequan 
             << " | " 
             << setw(11) << Current->HocLuc 
             << " | " 
             << setw(15) << Current->Ngaybatdau
             << " | " 
             << setw(12) << Current->Hoancanh 
             << " | " 
             << setw(10)  << (Current->LaMienGiam ? "Co" : "Khong") 
             << " |"     << endl;

        cout << "----------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        Current = Current->Next;
        index++; // Tang so thu tu 
    }
}

// Ham in danh sach phong theo dinh dang bang
void InDanhSachPhong(Phong* Head) {
    cout << "=================================================================================================================================" << endl;
    cout << " | " << setw(5)   << "STT" 
         << " | " << setw(10)  << "Id Phong" 
         << " | " << setw(30) <<  "Co day du do so vat chat" 
         << " | " << setw(19) <<  "So luong sinh vien" 
         << " | " << setw(25) <<  "Tong Tien Dien Nuoc" 
         << " | " << setw(20) <<  "Giai thuong phong" 
         << " |"     << endl;
    cout << "=================================================================================================================================" << endl;


    Phong* Current = Head;
    int index = 1; // Bien de dem so thu tu
    while (Current != NULL) {
        int soSinhVien = 0;
        SinhVien* svCurrent = Current->Danhsachsinhvien;
        while (svCurrent != NULL) {
            soSinhVien++;
            svCurrent = svCurrent->Next;
        }

        cout << " | " 
             << setw(5)  << index 
             << " | " 
             << setw(10) << Current->IdPhong
             << " | " 
             << setw(30) << (Current->Codayducosovatchat ? "Co" : "Khong") 
             << " | " 
             << setw(19) << soSinhVien 
             << " | " 
             << setw(25) << Current->TongTienDienNuoc 
             << " | " 
             << setw(20) << Current->GiaiThuongPhong 
             << " |"     << endl;

        cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;
        Current = Current->Next;
        index++; // Tang so thu tu
    }
}

// Ham tim sinh vien theo MSSV va in ra thong tin
SinhVien* TimSinhVienTheoMSSV(SinhVien* Head, const string& MSSV) {
    SinhVien* Current = Head;
    while (Current != NULL) {
        if (Current->MSSV == MSSV) {
            // In ra thong tin sinh vien
            cout << "Sinh Vien Tim Thay:" << endl;
            cout << "MSSV: " << Current->MSSV << endl;
            cout << "Ho va Ten: " << Current->Hovaten << endl;
            cout << "Lop: " << Current->Lop << endl;
            cout << "Que Quan: " << Current->Quequan << endl;
            cout << "Hoc Luc: " << Current->HocLuc << endl;
            cout << "Ngay Bat Dau: " << Current->Ngaybatdau << endl;
            cout << "Hoan Canh: " << Current->Hoancanh << endl;
            cout << "Mien Giam: " << (Current->LaMienGiam ? "Co" : "Khong") << endl;
            return Current; // Tim thay sinh vien
        }
        Current = Current->Next; // Di chuyen den sinh vien tiep theo
    }
    cout << "Khong Tim Thay Sinh Vien Voi Ma So: " << MSSV << endl;
    return NULL; // Khong tim thay
}

// Ham in danh sach sinh vien duoc mien giam
void InDanhSachSinhVienMienGiam(SinhVien* Head) {
    cout << "Danh Sach Sinh Vien Duoc Mien Giam:" << endl;
    SinhVien* Current = Head;
    while (Current != NULL) {
        if (Current->LaMienGiam) {
            cout << Current->Hovaten << " - MSSV: " << Current->MSSV << endl;
        }
        Current = Current->Next;
    }
}

// Ham in danh sach sinh vien cua tat ca cac phong
void InDanhSachSinhVienCuaTatCaPhong(Phong* Head) {
    if (Head == NULL) {
        cout << "Khong co phong nao trong danh sach!" << endl;
        return;
    }

    Phong* CurrentPhong = Head;
    while (CurrentPhong != NULL) {
        cout << "Danh Sach Sinh Vien Trong Phong ID: " << CurrentPhong->IdPhong << endl;
        InDanhSachSinhVien(CurrentPhong->Danhsachsinhvien);
        CurrentPhong = CurrentPhong->Next;
    }
}

// Ham in danh sach sinh vien duoc mien giam tien phong cua tat ca cac phong
void InDanhSachSinhVienMienGiamCuaTatCaPhong(Phong* Head) {
    if (Head == NULL) {
        cout << "Khong co phong nao trong danh sach!" << endl;
        return;
    }

    bool found = false; // Bien de kiem tra xem co sinh vien nao duoc mien giam hay khong
    Phong* CurrentPhong = Head;
    while (CurrentPhong != NULL) {
        SinhVien* CurrentSV = CurrentPhong->Danhsachsinhvien;
        cout << "Danh Sach Sinh Vien Duoc Mien Giam Trong Phong ID: " << CurrentPhong->IdPhong << endl;
        while (CurrentSV != NULL) {
            if (CurrentSV->LaMienGiam) {
                cout << CurrentSV->Hovaten << " - MSSV: " << CurrentSV->MSSV << endl;
                found = true; // Danh dau co sinh vien duoc mien giam
            }
            CurrentSV = CurrentSV->Next;
        }
        CurrentPhong = CurrentPhong->Next;
        cout << "---------------------------------------------------------------------" << endl;
    }

    if (!found) {
        cout << "Khong co sinh vien nao duoc mien giam trong danh sach." << endl;
    }
}

// Hàm xóa phòng theo ID
void XoaPhong(Phong*& Head, const string& IdPhong) {
    if (Head == NULL) {
        cout << "Danh sach phong rong!" << endl;
        return;
    }

    Phong* Current = Head;
    Phong* Previous = NULL;

    // Tim phong theo ID
    while (Current != NULL && Current->IdPhong != IdPhong) {
        Previous = Current;
        Current = Current->Next;
    }

    // Neu khong tim thay phong
    if (Current == NULL) {
        cout << "Phong khong ton tai!" << endl;
        return;
    }

    // Neu phong can xoa la phong dau danh sach
    if (Previous == NULL) {
        Head = Current->Next; // Cap nhat dau danh sach
    } else {
        Previous->Next = Current->Next; // Bo qua phong can xoa
    }

    // Giai phong bo nho
    while (Current->Danhsachsinhvien != NULL) {
        SinhVien* SinhVienTam = Current->Danhsachsinhvien;
        Current->Danhsachsinhvien = Current->Danhsachsinhvien->Next;
        delete SinhVienTam; // Giai phong bo nho cho sinh vien
    }
    delete Current; // Giai phong bo nho cho phong
    cout << "Xoa phong thanh cong!" << endl;
}
// Ham Main
int main() {
    Phong* DanhSachPhong = NULL;
    int LuaChon;

    do {
        cout << "\n--------------------- Menu -------------------------------" << endl;
        cout << "1. Nhap Phong" << endl;
        cout << "2. Nhap Sinh Vien Vao Phong" << endl;
        cout << "3. Nhap Sinh Vien Tai Vi Tri Bat Ki" << endl;
        cout << "4. Xoa Sinh Vien Tai Vi Tri Bat Ki" << endl;
        cout << "5. In Danh Sach Sinh Vien Trong Phong" << endl;
        cout << "6. In Danh Sach Cac Phong" << endl;
        cout << "7. Tim Sinh Vien Theo Ma So Sinh Vien" << endl;
        cout << "8. In Danh Sach Sinh Vien Duoc Mien Giam Tien Phong" << endl;
        cout << "9. In Danh Sach Sinh Vien Cua Tat Ca Phong" << endl; 
        cout << "10. In Danh Sach Sinh Vien Mien Giam Cua Tat Ca Phong" << endl; 
        cout << "11. Xoa Phong" << endl; 
        cout << "0. Thoat" << endl;
        cout << "\n-----------------------------------------------------------" << endl;
        cout << " Chon mot tuy chon: ";
		
    
        // Nhap lua chon va kiem tra tinh hop le
while (true) {
    cout << "Nhap lua chon (0-11): ";
    cin >> LuaChon;

    // Kiem tra xem nguoi dung co nhap so hay khong
    if (cin.fail() || LuaChon > 10 || LuaChon < 0) {
    	
        cin.clear(); // Xoa trang thai loi nhap
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bo qua dong nhap
        cout << "Loi: Vui long nhap mot so tu 0 den 11." << endl; 
    } else {
        break; // Thoat vong lap neu nhap hop le
    }
}
        switch (LuaChon) {
            case 1: {
                NhapPhong(DanhSachPhong);
                break;
            }
            case 2: {
                string IdPhong;
                Phong* PhongHienTai = NULL;
                do {
			
                cout << "Nhap ID Phong De Them Sinh Vien: ";
                cin >> IdPhong;
                PhongHienTai = DanhSachPhong;
                while (PhongHienTai != NULL && PhongHienTai->IdPhong != IdPhong) {
						PhongHienTai = PhongHienTai->Next;
                }
                if (PhongHienTai == NULL) {
                	cout << "Phong Khong Ton Tai! Vui Long Nhap Lai." << endl;
                }
            } while (PhongHienTai == NULL);
                    nhapSinhVien(PhongHienTai->Danhsachsinhvien);
                break;
            }
            case 3: {
                string IdPhong;
                Phong* PhongHienTai = NULL;
            do {
                cout << "Nhap ID Phong De Nhap Sinh Vien Tai Vi Tri: ";
                cin >> IdPhong;
                PhongHienTai = DanhSachPhong;
                while (PhongHienTai != NULL && PhongHienTai->IdPhong != IdPhong) {
                    PhongHienTai = PhongHienTai->Next;
                }
                if (PhongHienTai == NULL) {
                	cout << "Phong Khong Ton Tai! Vui Long Nhap Lai." << endl;
                }
            } while (PhongHienTai == NULL);
                    {
					SinhVien SinhVienMoi;
                    cout << "Nhap Thong Tin Sinh Vien:" << endl;
                    cout << "| MSSV: ";
                    cin >> SinhVienMoi.MSSV;
                    cin.ignore();

                    cout << "| Ho Va Ten: ";
                    getline(cin, SinhVienMoi.Hovaten);

                    cout << "| Lop: ";
                    getline(cin, SinhVienMoi.Lop);

                    cout << "| Que Quan: ";
                    getline(cin, SinhVienMoi.Quequan);

                    cout << "| Hoc Luc (xuat sac/gioi/khac): ";
                    getline(cin, SinhVienMoi.HocLuc);

                    cout << "| Ngay Bat Dau (dd/mm/yyyy): ";
                    getline(cin, SinhVienMoi.Ngaybatdau);

                    cout << "| Hoan Canh (ho ngheo/mo coi/binh thuong): ";
                    getline(cin, SinhVienMoi.Hoancanh);

                    SinhVienMoi.LaMienGiam = (SinhVienMoi.Hoancanh == "ho ngheo" || SinhVienMoi.Hoancanh == "mo coi") && (SinhVienMoi.HocLuc == "xuat sac");

                    SinhVienMoi.Next = NULL; // Khoi tao con tro tiep theo
                    int viTri;
                    cout << "Nhap Vi Tri De Chen Sinh Vien: ";
                    cin >> viTri;
                    ThemSinhVienTaiViTri(PhongHienTai->Danhsachsinhvien, SinhVienMoi, viTri);
                    
                    
                    cout << "Phong Khong Ton Tai!" << endl;
                }
                break;
            }
            case 4: {
                string IdPhong;
                Phong* PhongHienTai = NULL;
            do {
                cout << "Nhap ID Phong De Xoa Sinh Vien Tai Vi Tri: ";
                cin >> IdPhong;
                PhongHienTai = DanhSachPhong;
                while (PhongHienTai != NULL && PhongHienTai->IdPhong != IdPhong) {
                    PhongHienTai = PhongHienTai->Next;
                }
                if (PhongHienTai == NULL) {
                	cout << "Phong Khong Ton Tai! Vui Long Nhap Lai." << endl;
                }
            } while (PhongHienTai == NULL);
                    int viTri;
                    cout << "Nhap Vi Tri De Xoa Sinh Vien: ";
                    cin >> viTri;
                    XoaSinhVienTaiViTri(PhongHienTai->Danhsachsinhvien, viTri);
                break;
            }

            case 5: {
                string IdPhong;
                Phong* PhongHienTai = NULL;
                do {
                cout << "Nhap ID Phong De In Danh Sach Sinh Vien: ";
                cin >> IdPhong;
                PhongHienTai = DanhSachPhong;
                while (PhongHienTai != NULL && PhongHienTai->IdPhong != IdPhong) {
                    PhongHienTai = PhongHienTai->Next;
                }
                if (PhongHienTai == NULL) {
                	cout << "Phong Khong Ton Tai! Vui Long Nhap Lai." << endl;
                }
            } while (PhongHienTai == NULL);
                    InDanhSachSinhVien(PhongHienTai->Danhsachsinhvien);
                break;
            }
            case 6: {
                InDanhSachPhong(DanhSachPhong);
                break;
            }
            case 7: {
    string MSSV;
    cout << "Nhap Ma So Sinh Vien Can Tim: ";
    cin >> MSSV;
    TimSinhVienTheoMSSV(DanhSachPhong->Danhsachsinhvien, MSSV);
    break;
}
            case 8: {
                string IdPhong;
                Phong* PhongHienTai = NULL;
            do {
                cout << "Nhap ID Phong De In Danh Sach Sinh Vien Duoc Mien Giam Tien Phong: ";
                cin >> IdPhong;
                PhongHienTai = DanhSachPhong;
                while (PhongHienTai != NULL && PhongHienTai->IdPhong != IdPhong) {
                    PhongHienTai = PhongHienTai->Next;
                }
                if (PhongHienTai == NULL) {
                	cout <<"Phong Khong Ton Tai! Vui Long Nhap Lai." << endl;
                }
            } while (PhongHienTai == NULL);

                    InDanhSachSinhVienMienGiam(PhongHienTai->Danhsachsinhvien);
                break;
            }
            case 9: {
            InDanhSachSinhVienCuaTatCaPhong(DanhSachPhong); 
            break;
            }
            case 10: {
            InDanhSachSinhVienMienGiamCuaTatCaPhong(DanhSachPhong); 
            break;
            }
            case 11: { 
            string IdPhong;
            cout << "Nhap ID phong can xoa: ";
            cin >> IdPhong;
            XoaPhong(DanhSachPhong, IdPhong);
            break;
        }
            case 0:
                cout << "Thoat Chuong Trinh." << endl;
                break;
            default:
                cout << "Lua Chon Khong Hop Le. Vui Long Thu Lai." << endl;
        }
    } while (LuaChon > 0);

    // Giai phong bo nho
    while (DanhSachPhong != NULL) {
        Phong* PhongTam = DanhSachPhong;
        DanhSachPhong = DanhSachPhong->Next;
        while (PhongTam->Danhsachsinhvien != NULL) {
            SinhVien* SinhVienTam = PhongTam->Danhsachsinhvien;
            PhongTam->Danhsachsinhvien = PhongTam->Danhsachsinhvien->Next;
            delete SinhVienTam;
        }
        delete PhongTam;
    }

    return 0;
}
