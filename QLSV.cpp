#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <mylib.h>
#include <string>
#include <iostream>
#include <fstream>

#define MAXLOPTINCHI 100000

using namespace std;

//=============================== DS MON HOC CAY NHI PHAN TIM KIEM =====================
struct MONHOC{
	char MAMH[10];
	char TENMH[35];
	int STCLT;
	int STCTH; 
};

struct nodeMH{
	MONHOC mh;
	nodeMH *left;
	nodeMH *right;
};

typedef nodeMH *PTRMH;



struct DanhSachMonHoc{
		int soluong=0;
		MONHOC* node=new MONHOC[100];
		
};



//=============================== SINH VIEN DS LIEN KET DON ============================

struct SinhVien{
	char MASV[15];
	char HO[30];
	char TEN[10];
	char SDT[12];
	char PHAI[4];
	char MALOP[15];
};

struct nodeSV {
	SinhVien sv;
	nodeSV* next;
};

typedef nodeSV* PTRSV;

struct DanhSachSV{
	int soluong;
	SinhVien* node =new SinhVien[100];
};
        
//============================ DANG KY DS LIEN KET DON =======================
struct DangKy {
	char MASV[15];
	float DIEM;
	boolean HUYDANGKY = false;	
};

struct nodeDangKy {
	DangKy dangky;
	nodeDangKy* next;
};

typedef nodeDangKy* PTRDK;


// LOP TIN CHI DS TUYEN TINH MANG CON TRO

struct LopTinChi{
	int MALOPTC;
	char MAMH[10];
	char NIENKHOA[10];
	int HOCKY;
	int NHOM;
	int SOSVMIN;
	int SOSVMAX;
	
	boolean HUYLOP = false;
	PTRDK First_DSSVDK = NULL;
};

struct LIST_LTC {
	int soluong = 0;
	LopTinChi *nodesltc[MAXLOPTINCHI];
};

// =========================== END KHAI BAO ========================

int XacNhan (char *S){
	cout<<S;
	char kt;
	do{
		kt=toupper(getch());
	}while(kt!='Y'&&kt!='N');
	cout<<kt;
	return kt=='Y';
}

int DK_Reccount(PTRDK &FirstDK);
void DK_Insert_last(PTRDK &FirstDK, DangKy dk);

//==========================MON HOC=================


// tim kiem MH theo ma so khong de qui
PTRMH MH_SearchMS (PTRMH &root,char *x)
{  const int STACKSIZE = 500;
   PTRMH Stack[STACKSIZE];
   int sp=  -1;	// Khoi tao Stack rong
   PTRMH p=root;
   while (p!=NULL )
   {
      if(stricmp(p->mh.MAMH,x)==0)
      	return p;

      if (p->right != NULL)
		Stack[++sp]= p->right;
      if (p->left != NULL)
		p=p->left;
      else  if (sp==-1)
		break;
	  else		 p=Stack[sp--];
   }
   return NULL;
}


// them node mon hoc vao cay nhi phan
void MH_Insert(PTRMH &p, MONHOC mh)
{ 
   if(p == NULL)    // nut p hien tai se la nut la
   {
     p = new nodeMH;
     p->mh = mh;
     p->left = NULL;     p->right = NULL;  
   }
   else
    if(stricmp(mh.MAMH,p->mh.MAMH)<0)
    	MH_Insert(p->left, mh);
    else if(stricmp(mh.MAMH,p->mh.MAMH)>0)
		MH_Insert(p->right, mh);
}

// Tao cay mon hoc 
void MH_Create(PTRMH &root)
{ MONHOC mh;
	PTRMH temp;
  	while(1){
	 
  	fflush(stdin);
  	cout<<"Nhap ma mon hoc: ";
  	gets(mh.MAMH);
  	if(strcmp(mh.MAMH,"0")==0) break;
  	temp=MH_SearchMS(root,mh.MAMH);
  	if(temp!=NULL) {
  		cout<<"Ma bi trung\n";
  		continue;
	  }
  	cout<<"Nhap ten mon hoc: ";
  	gets(mh.TENMH);
  	cout<<"Nhap so tin chi ly thuyet: ";
    cin >> mh.STCLT;
    cout<<"Nhap so tin chi thuc hanh: ";
    cin >> mh.STCTH;
        
    MH_Insert(root,mh);
     
    }
}


//Show NLR
void MH_Show(PTRMH root)
{

   if (root != NULL) 
   {
      printf("\n   %10s  %-15s %-8d %8d"   , root->mh.MAMH, root->mh.TENMH,root->mh.STCLT,root->mh.STCTH);
      MH_Show(root->left);
      MH_Show(root->right);
   }
}

// dem tong so nut cua cay mon hoc
void MH_DemSoNut(PTRMH &root, int &sl)
{

   if (root != NULL) 
   {
      sl++;
      MH_DemSoNut(root->left,sl);
      MH_DemSoNut(root->right,sl);
   }
}

// duyet cay ghi vao file 
void MH_traverseWriteToFile(PTRMH root,ofstream &outfile){
	MONHOC mh;
	if(root != NULL){
		outfile<<root->mh.MAMH<<endl;
		outfile<<root->mh.TENMH<<endl;
		outfile<<root->mh.STCLT<<endl;
		outfile<<root->mh.STCTH<<endl;
		MH_traverseWriteToFile(root->left, outfile);
		MH_traverseWriteToFile(root->right, outfile);
	}
}

// ghi file mon hoc
void MH_ghiFileMonHoc(PTRMH &root){
	ofstream outfile;
	outfile.open("MonHoc.txt");
	int slmh =0;
	MH_DemSoNut(root,slmh);
	outfile<<slmh<<endl;
	MH_traverseWriteToFile(root,outfile);
	outfile.close();
}

// doc file mon hoc 
void MH_docFileMonHoc(PTRMH &root){
	MONHOC mh;
	ifstream filein;
	root = NULL;
	filein.open("MonHoc.txt",ios::in);
	int slmh;
	filein>>slmh;
	filein.ignore();
	for(int i =0; i<slmh; i++){
		filein.getline(mh.MAMH , 10);
		filein.getline(mh.TENMH,35);
		filein>>mh.STCLT;
		filein.ignore();
		filein>>mh.STCTH;
		filein.ignore();
		MH_Insert(root, mh);	
	}
	cout<<"\n Doc file MH thanh cong";
	filein.close();
	
}

PTRMH rp;

void  MH_remove_case_3(PTRMH  &r)
{
  	if (r->left != NULL)
    	MH_remove_case_3 (r->left);
   //den day r la nut cuc trai cua cay con ben phai co nut goc la rp}
    else {
   		//Chep noi dung cua r sang rp ";
   		rp->mh = r->mh;	//  de lat nua free(rp)
   		rp = r;           	
   		r = rp->right;
	}
}
void  MH_remove (char *x ,  PTRMH &p )
{
	if (p == NULL)  printf ("Khong tim thay");
	else
	  	if (stricmp(x,p->mh.MAMH)<0)   MH_remove (x, p->left);
	  	else if (stricmp(x,p->mh.MAMH)>0)
			MH_remove (x, p->right);
	    else {  	// p->key = x
			rp = p;
            if (rp->right == NULL)  p = rp->left;   
			// p là nút lá hoac la nut chi co cay con ben trai
		 	else if (rp->left == NULL) p = rp->right;  // p là nut co cay con ben phai
			else MH_remove_case_3 (rp->right);
		delete rp;
	    }
}


void MH_Delete(PTRMH &root){
	MH_Show(root);
	char mamh[10];
	cout<<"\nNhap ma mon hoc muon xoa: ";
	gets(mamh);
	MH_remove(mamh, root);
}

void MH_Sua(PTRMH &root){
	MH_Show(root);
	char mamh[10];
	cout<<"\nNhap ma mon hoc muon sua: ";
	gets(mamh);
	int stc;
	cout<<"\nNhap ten mon hoc: ";
	gets(MH_SearchMS(root,mamh)->mh.TENMH);
	cout<<"\nNhap so tin chi ly thuyen: ";
	cin>>stc;
	MH_SearchMS(root,mamh)->mh.STCLT=stc;
	cout<<"\nNhap so tin chi thuc hanh: ";
	cin>>stc;
	MH_SearchMS(root,mamh)->mh.STCTH=stc;
}

void MH_Insert_dstt(DanhSachMonHoc &listMH, MONHOC mh){
	listMH.node[listMH.soluong]=mh;
	listMH.soluong +=1;
}

void MH_ThemMHVaoDSTT(PTRMH &root, DanhSachMonHoc &listMH)
{

   if (root != NULL) 
   {
      MH_Insert_dstt(listMH,root->mh);
      MH_ThemMHVaoDSTT(root->left,listMH);
      MH_ThemMHVaoDSTT(root->right,listMH);
   }
}

void MH_Selection_Sort(DanhSachMonHoc &listMH){
  int vitrimin;
  int i,j;
  MONHOC min;
  for (i=0; i< listMH.soluong-1; i++){
    min = listMH.node[i];    vitrimin=i;
    for (j=i+1; j<listMH.soluong; j++)
      if (stricmp(listMH.node[j].TENMH,min.TENMH)<0){
	  	min = listMH.node[j];	vitrimin=j;
      }
    // Doi cho 2 phan tu A[i] va A[vitrimin]
    min = listMH.node[vitrimin] ;    listMH.node[vitrimin] = listMH.node[i];    listMH.node[i] = min;
  }
}

void MH_ShowDSTT(DanhSachMonHoc &listMH)
{
	int i;
	if(listMH.soluong == 0)
	{
		printf("\n     Danh sach khong co phan tu");
		return;
	}
	for(i = 0 ; i < listMH.soluong ; i++)
		
		printf("\n   %10s  %-15s %-8d %8d"   , listMH.node[i].MAMH, listMH.node[i].TENMH,listMH.node[i].STCLT,listMH.node[i].STCTH);
		
	getch();
	delete [] listMH.node;
}


void MH_SapXep(PTRMH &root){ 
	DanhSachMonHoc listMH;
	MH_ThemMHVaoDSTT(root,listMH);
	MH_Selection_Sort(listMH);
	MH_ShowDSTT(listMH);
}

//==========================LOP TIN CHI========================


// ma LTC tu dong tang 
int maTuDongTang(LIST_LTC &list_ltc){
	if(list_ltc.soluong==0) return 1; 
	return list_ltc.nodesltc[list_ltc.soluong-1]->MALOPTC+1;
}

// search ltc theo ma
int LTC_Search_theoma(LIST_LTC &list_ltc, int x)
{
	for ( int i =0 ; i <list_ltc.soluong ; i++)
  	     if (list_ltc.nodesltc[i]->MALOPTC == x) return i;
	return -1;
}


// tao lop tin chi
int Create_LTC(LIST_LTC &list_ltc, LopTinChi &ltc, PTRMH &root){
	PTRMH p;	
	cout<<"Nhap thong tin lop tin chi\n";
	ltc.MALOPTC=maTuDongTang(list_ltc); fflush(stdin);
	do{
	
		cout<<"\nNhap Ma mon hoc: ";
		gets(ltc.MAMH);
		if(stricmp(ltc.MAMH,"0")==0) return 0;
		p=MH_SearchMS(root,ltc.MAMH);
		if(p==NULL) {
			cout<<"\n Ma mon khong ton tai.";
			continue;
		}
		cout<<"Nhap Nien khoa: "; fflush(stdin);
		gets(ltc.NIENKHOA);
		cout<<"Nhap Hoc ki: ";
		cin>>ltc.HOCKY;
		cout<<"Nhap Nhom: ";
		cin>>ltc.NHOM;
		cout<<"Nhap so sinh vien min: ";
		cin>>ltc.SOSVMIN;
		cout<<"Nhap so sinh vien max: ";
		cin>>ltc.SOSVMAX;
		ltc.HUYLOP = false;
		ltc.First_DSSVDK=NULL;
		fflush(stdin);
		return 1;
	}while(true);
}

// tao danh sach lop tin chi
// them lop tin chi
void Create_List_LTC(LIST_LTC &list_ltc,PTRMH &root){
	LopTinChi ltc;
	
	while(list_ltc.soluong<MAXLOPTINCHI){
		if (Create_LTC(list_ltc, ltc,root)==0)    
		   return;
		list_ltc.nodesltc[list_ltc.soluong] = new LopTinChi;
		//gan gia tri lop tin chi them vao vao con tro lop tin chi cuoi mang
		*list_ltc.nodesltc[list_ltc.soluong] = ltc;
		list_ltc.soluong +=1;
	}
}

void LTC_Insert(LIST_LTC &list_ltc, LopTinChi ltc){
	list_ltc.nodesltc[list_ltc.soluong]=new LopTinChi;
	*list_ltc.nodesltc[list_ltc.soluong]=ltc;
	list_ltc.soluong +=1;
}

// duyet danh sach lop tin chi 
void LTC_traverse(LIST_LTC &list_ltc){
	char huylop[10];
	printf ("                     DANH SACH LOP TIN CHI \n");
 	printf ("  Stt   Ma lop   Ma mon   Nhom   Nien khoa     Hoc Ky    So sv max     So sv min     Huy dang ky\n");
	for (int i =0 ; i < list_ltc.soluong ; i++){
		if(list_ltc.nodesltc[i]->HUYLOP==false)	strcpy(huylop,"");
		else strcpy(huylop,"da huy");
		printf ("%8d %5d  %-10s  %-8d  %10s  %5d  %5d   %5d   %10s \n", 
		  i+1,
		  list_ltc.nodesltc[i]->MALOPTC,
		  list_ltc.nodesltc[i]->MAMH,
		  list_ltc.nodesltc[i]->NHOM,
		  list_ltc.nodesltc[i]->NIENKHOA,
		  list_ltc.nodesltc[i]->HOCKY,
		  list_ltc.nodesltc[i]->SOSVMAX,
		  list_ltc.nodesltc[i]->SOSVMIN,
		  huylop);
	}
	
  		
 	getch();
}

int LTC_Empty(LIST_LTC &list_ltc)
{     return(list_ltc.soluong == 0 ? 1 : 0);
}

// xoa LTC theo ma
void LTC_Delete_theoma (LIST_LTC &list_ltc)
{	int i;
	cout<<"Nhap ma lop tin chi muon xoa: ";
	cin>>i;
	int j;
	int temp;
	if(i <= 0 || i > list_ltc.soluong)
		printf("Vi tri xoa khong phu hop.");
	else
		if(LTC_Empty(list_ltc))
			printf("Danh sach khong co phan tu.");
		else
		{
			for(j = i;  j< list_ltc.soluong ; j++)
				list_ltc.nodesltc[j-1] = list_ltc.nodesltc[j];
			list_ltc.soluong--;
		}
}

//
void LTC_Sua_theoma(LIST_LTC &list_ltc,PTRMH &root){
	char x[10];
	int temp;
	int maltc;
	cout<<"Nhap ma lop tin chi muon sua: ";
	cin>>maltc;
	int vitri=LTC_Search_theoma(list_ltc,maltc);
	if(vitri==-1) cout<<"Khong tim thay.";
	else{
		printf ("   Ma lop   Ma mon   Nhom   Nien khoa     Hoc Ky    So sv max     So sv min   \n");
  		printf (" %5d  %-10s  %-8d  %10s  %5d  %5d   %5d    \n", 
	  		list_ltc.nodesltc[vitri]->MALOPTC,
	  		list_ltc.nodesltc[vitri]->MAMH,
	  		list_ltc.nodesltc[vitri]->NHOM,
	  		list_ltc.nodesltc[vitri]->NIENKHOA,
	  		list_ltc.nodesltc[vitri]->HOCKY,
	  		list_ltc.nodesltc[vitri]->SOSVMAX,
	  		list_ltc.nodesltc[vitri]->SOSVMIN);
	  	cout<<"\nNHAN ENTER DE BO QUA (KHONG SUA)\n";
	  	cout<<"Nhap Ma mon hoc: ";	fflush(stdin);
		gets(x);
		PTRMH p = MH_SearchMS(root,x);
		
		if(stricmp(x,"0")!=0){
			if(p==NULL){
				cout<<"\n Ma mon hoc khong ton tai";
				getch();
				return;
			}
			else	strcpy(list_ltc.nodesltc[vitri]->MAMH,x);
		}  
	  	cout<<"Nhap Nien khoa: "; fflush(stdin);
		gets(x);
		if(stricmp(x,"0")!=0)	strcpy(list_ltc.nodesltc[vitri]->NIENKHOA,x);
		cout<<"Nhap Hoc ki: ";
		cin>>temp;
		if(temp!=0)	list_ltc.nodesltc[vitri]->HOCKY=temp;
		cout<<"Nhap Nhom: ";
		cin>>temp;
		if(temp!=0)	list_ltc.nodesltc[vitri]->NHOM=temp;
		cout<<"Nhap so sinh vien min: ";
		cin>>temp;
		if(temp!=0)	list_ltc.nodesltc[vitri]->SOSVMIN=temp;
		cout<<"Nhap so sinh vien max: ";
		cin>>temp;
		if(temp!=0)	list_ltc.nodesltc[vitri]->SOSVMAX=temp;
	}
	
 	getch();
}




// ghi file lop tin chi
void LTC_ghiFile(LIST_LTC &list_ltc){
	PTRDK p;
	ofstream outfile;
	outfile.open("LopTinChi.txt");
	outfile<<list_ltc.soluong<<endl;	//ghi so luong lop
	for(int i=0; i<list_ltc.soluong;i++){
		outfile<<list_ltc.nodesltc[i]->MALOPTC<<endl;
		outfile<<list_ltc.nodesltc[i]->MAMH<<endl;
		outfile<<list_ltc.nodesltc[i]->NHOM<<endl;
		outfile<<list_ltc.nodesltc[i]->HOCKY<<endl;
		outfile<<list_ltc.nodesltc[i]->NIENKHOA<<endl;
		outfile<<list_ltc.nodesltc[i]->SOSVMIN<<endl;
		outfile<<list_ltc.nodesltc[i]->SOSVMAX<<endl;
		if(list_ltc.nodesltc[i]->HUYLOP==true)
		outfile<<1<<endl;
		else outfile<<0<<endl;
		int slsv=DK_Reccount(list_ltc.nodesltc[i]->First_DSSVDK);	//ghi so luong sinh vien cua lop
		outfile<<slsv<<endl;
		p=list_ltc.nodesltc[i]->First_DSSVDK;
		while(p!=NULL){
			outfile<<p->dangky.MASV<<endl;
			outfile<<p->dangky.DIEM<<endl;
			if(p->dangky.HUYDANGKY==true)
			outfile<<1<<endl;
			else outfile<<0<<endl;
			
			p=p->next;	
		}
	}
	
	outfile.close();
}



void LTC_docFile(LIST_LTC &list_ltc){
	LopTinChi ltc;
	DangKy dk;
	ifstream filein;
	int slsv,slltc;
	list_ltc.soluong=0;
	filein.open("LopTinChi.txt",ios::in);
	filein>>slltc;
	filein.ignore();
	for(int i =0; i<slltc; i++){
		filein>>ltc.MALOPTC;
		filein.ignore();
		filein.getline(ltc.MAMH, 10);
		filein>>ltc.NHOM;
		filein.ignore();
		filein>>ltc.HOCKY;
		filein.ignore();
		filein.getline(ltc.NIENKHOA,10);
		filein>>ltc.SOSVMIN;
		filein.ignore();
		filein>>ltc.SOSVMAX;
		filein.ignore();
		int kt;
		filein>>kt;
		filein.ignore();
		if(kt==1)	ltc.HUYLOP=true;
		else	ltc.HUYLOP=false;
		filein>>slsv;
		filein.ignore();
		ltc.First_DSSVDK=NULL;
		for(int j=0; j<slsv;j++){
			filein.getline(dk.MASV,15);
			filein>>dk.DIEM;
			filein.ignore();
			filein>>kt;
			filein.ignore();
			if(kt==1)	dk.HUYDANGKY=true;
			else	dk.HUYDANGKY=false;
			DK_Insert_last(ltc.First_DSSVDK,dk);
		}
		LTC_Insert(list_ltc, ltc);
			
	}
	cout<<"\n Doc file LTC thanh cong";
	filein.close();
	
}




// =============================== SINH VIEN ======================================
// CLEAR DANH SACH SINH VIEN
void SV_clearlist(PTRSV &First)
{
   PTRSV p;   
   p = First;
   while(First != NULL)
   {
      p = First;
      First = First->next;
      delete p;
   }
}

//TIM SV THEO ....
PTRSV SV_search_infosv(PTRSV First, char *x){
	PTRSV p;
	for(p=First; p!= NULL; p=p->next){
		if(stricmp(p->sv.MASV,x)==0)
		return p;
	}
	return NULL;
}

//THEM SV VAO CUOI
void SV_Insert_last(PTRSV &FirstSV, SinhVien x){
	PTRSV tmp = new nodeSV;
	tmp->sv = x;
	
	if(FirstSV==NULL){
		tmp->next = FirstSV;
		FirstSV = tmp;
	} 
		
	else 
	{
	  PTRSV p = FirstSV;
	  while(p->next!=NULL)
			p = p->next;
	
	   p->next = tmp;
	   tmp->next=NULL;
	}
    
}

//KHOI TAO DANH SACH SINH VIEN
void SV_Create_DSSV(PTRSV &First)
{ 
	PTRSV Last,p, temp;
    SinhVien sv;

    char maso[15],c;
	  	
    
  do
  {
  		printf("Ma so sinh vien: ");
		gets(sv.MASV);
		if(stricmp(sv.MASV,"0")==0) return;
		temp=SV_search_infosv(First,sv.MASV);
		if(temp!=NULL)	{
			cout<<"\nMa so bi trung.\n";
			continue;	
		}
		printf("Ho sinh vien: ");
		gets(sv.HO);
		printf("Ten sinh vien: ");
		gets(sv.TEN);
		cout<<"Ma lop: ";
		gets(sv.MALOP);
		cout<<"Phai: ";
		gets(sv.PHAI);
		cout<<"So dien thoai: ";
		gets(sv.SDT);
		fflush(stdin);
		
		SV_Insert_last(First,sv);
	}while(1);
}

// duyet DS SINH VIEN
void SV_traverse(PTRSV First)
{
   PTRSV p;
   int stt = 0;
   p = First; 
   if(p == NULL){
   	printf("\n   (Khong co sinh vien trong danh sach)");
   	getche();
   	return;
   }
      
   printf("\n       Danh sach sinh vien: ");
   printf("\n     STT       MSSV       HO           TEN            MA LOP          PHAI            SDT");
   while(p != NULL)
   {
      printf("\n   %5d %10s  %-15s %-10s %15s %5s %15s"   , ++stt, p->sv.MASV, p->sv.HO,p->sv.TEN, p->sv.MALOP, p->sv.PHAI, p->sv.SDT);
      p = p->next;
   }
   getche();
}


//luu file SV
int SV_SaveFile (PTRSV &FirstSV) {
	FILE *f = fopen ("SinhVien.txt", "wb");
	if (f==NULL) return 0;
	for (PTRSV p=FirstSV ; p!=NULL ; p=p->next)
	  fwrite (&p->sv, sizeof (SinhVien), 1, f);
	fclose (f);
	cout<<"Da luu file";
	getche();
	return 1;  
}

//mo file SV 
int SV_OpenFile (PTRSV &FirstSV) {
	PTRSV p;  SinhVien sv ;
	FILE *f = fopen ("SinhVien.txt", "rb");
	if (f==NULL) 
	  return 0; // mo file khong duoc
	SV_clearlist(FirstSV);
	while  (fread (&sv, sizeof (SinhVien), 1, f)== 1 ){
		SV_Insert_last (FirstSV , sv);
	} 
	fclose (f);
	cout<<"\nDoc file SV thanh cong";
	
	return 1;  
}

//THEM SV VAO DS SINH VIEN LK DON BANG MA LOP
void SV_Them_SV_theo_malop(PTRSV &FirstSV){
	PTRSV p,temp, Last;
	SinhVien sv;
	cout<<"Nhap ma lop: ";
	gets(sv.MALOP);
	do
   {
  		printf("Ma so sinh vien: ");
		gets(sv.MASV);
		if(stricmp(sv.MASV,"0")==0) return;
		temp=SV_search_infosv(FirstSV,sv.MASV);
		if(temp!=NULL)	{
			cout<<"\nMa so bi trung.\n";
			continue;	
		}
		printf("Ho sinh vien: ");
		gets(sv.HO);
		printf("Ten sinh vien: ");
		gets(sv.TEN);
		cout<<"Phai: ";
		gets(sv.PHAI);
		cout<<"So dien thoai: ";
		gets(sv.SDT);
		fflush(stdin);
		SV_Insert_last(FirstSV,sv);
	}while(1);
}

void SV_Delete_after(PTRSV p){
	PTRSV q;
	// neu p la NULL hoac p chi nut cuoi
	if((p == NULL) || (p->next == NULL))
      printf("khong xoa sinh vien nay duoc");
    else{
    	q=p->next;
    	p->next=q->next;
    	delete q;
	}
}

void SV_Delete_first(PTRSV &FirstSV){
	PTRSV p;
	p=FirstSV;
	FirstSV=p->next;
	delete p;
}

PTRSV SV_search_malopmasv(PTRSV FirstSV, char *malop, char *masv){
	PTRSV p;
	for(p=FirstSV; p!= NULL; p=p->next){
		if(stricmp(p->sv.MASV,masv)==0 && stricmp(p->sv.MALOP,malop)==0)
		return p;
	}
	return NULL;
}

//XOA SINH VIEN
void SV_Xoa_SV_theo_malop(PTRSV &FirstSV){
	PTRSV p;
	char malop[15], masv[15];
	cout<<"Nhap ma lop: ";	fflush(stdin);
	gets(malop);
	
	printf("\n       Danh sach sinh vien lop %s: ", malop);
   	printf("\n     STT       MSSV       HO           TEN         PHAI            SDT");
   	p=FirstSV;
   	int stt =0;
   	while(p != NULL){
   		if(stricmp(p->sv.MALOP,malop)==0)
      		printf("\n   %5d %10s  %-15s %-10s %5s %15s"   , ++stt, p->sv.MASV, p->sv.HO,p->sv.TEN, p->sv.PHAI, p->sv.SDT);
      	p = p->next;
    }
    if(stt==0) {
    	cout<<"\nKhong co sinh vien.";
    	getch();
		return;
	}
	while (1){
	
	   cout<<"\nNhap ma sinh vien muon xoa: ";fflush(stdin);
	   gets(masv);
	   if(stricmp(masv,"0")==0)	return;
	   
		p= SV_search_malopmasv(FirstSV,malop,masv);
		if(p==NULL){
		    cout<<"\nKhong ton tai";
		    getche();
		}
		else{
			cout<<"\n\tHo\tTen";
		 	cout<<"\n\t"<<p->sv.HO<<"\t"<<p->sv.TEN;
		 	int yn = XacNhan("\nBan co muon xoa khong? (Y/N): ");
			if(yn==1){
				if(p==FirstSV){
					SV_Delete_first(FirstSV);
				}
				else{
					PTRSV temp = FirstSV;
					while(temp->next != p){
						temp=temp->next;
					}
					SV_Delete_after(temp);
				}
				cout<<"\nXoa thanh cong";
				getch();
			}
		}
	}
}
// SUA SINH VIEN THEO MA LOP
void SV_Sua_SV_theo_malop(PTRSV &FirstSV){
	PTRSV p;
	char malop[15], masv[15];
	cout<<"Nhap ma lop: ";	fflush(stdin);
	gets(malop);
	
	printf("\n       DANH SACH SINH VIEN LOP %s: ",malop);
   	printf("\n     STT       MSSV       HO           TEN          PHAI            SDT");
   	p=FirstSV;
   	int stt =0;
   	while(p != NULL){
   		if(stricmp(p->sv.MALOP,malop)==0)
      		printf("\n   %5d %10s  %-15s %-10s %5s %15s"   , ++stt, p->sv.MASV, p->sv.HO,p->sv.TEN, p->sv.PHAI, p->sv.SDT);
      	p = p->next;
    }
    if(stt==0) {
    	cout<<"\nKhong co sinh vien.";
    	getch();
		return;
	}
	while (1){
	
	   cout<<"\nNhap ma sinh vien muon sua: ";fflush(stdin);
	   gets(masv);
	   if(stricmp(masv,"0")==0)	return;
	   p= SV_search_malopmasv(FirstSV,malop,masv);
	   if(p==NULL) cout<<"\n Khong ton tai.";
	   SinhVien sv;
	   cout<<"\nNHAP 0 DE BO QUA (KHONG SUA)\n";
	   cout<<"\nNhap ho: "; fflush(stdin);
	   gets(sv.HO);
	   if(stricmp(sv.HO,"0")!=0)	strcpy(p->sv.HO,sv.HO);
	   cout<<"\nNhap ten: "; fflush(stdin);
	   gets(sv.TEN);
	   if(stricmp(sv.TEN,"0")!=0)	strcpy(p->sv.TEN,sv.TEN);
	   cout<<"\nNhap phai: "; fflush(stdin);
	   gets(sv.PHAI);
	   if(stricmp(sv.PHAI,"0")!=0)	strcpy(p->sv.PHAI,sv.PHAI);
	   cout<<"\nNhap sdt: "; fflush(stdin);
	   gets(sv.SDT);
	   if(stricmp(sv.SDT,"0")!=0)	strcpy(p->sv.SDT,sv.SDT);
	}
}


void SV_Insert_dstt(DanhSachSV &listSV, SinhVien sv){
	listSV.node[listSV.soluong]=sv;
	listSV.soluong +=1;
}

void SV_ThemSVVaoDSTT(PTRSV &FirstSV, char* malop, DanhSachSV &listSV){
	PTRSV p=FirstSV;
	while(p!=NULL){
		if(stricmp(p->sv.MALOP,malop)==0)
			SV_Insert_dstt(listSV,p->sv);
		p=p->next;
	}
}
void SV_SapXepTenHo(DanhSachSV &listSV){
	int vitrimin;
	SinhVien min;
  	int i,j;
  	for (i=0; i< listSV.soluong-1; i++){
    	min = listSV.node[i];    vitrimin=i;
    	for (j=i+1; j<listSV.soluong; j++)
      		if (stricmp(listSV.node[j].TEN,min.TEN)<0){
	  			min = listSV.node[j];	vitrimin=j;
			}
	  		else if(stricmp(listSV.node[j].TEN,min.TEN)==0){
	  			if(stricmp(listSV.node[j].HO,min.HO)<0){
	  				min = listSV.node[j];	vitrimin=j;
				}
	  				
      		}
    	min = listSV.node[vitrimin] ;    listSV.node[vitrimin] = listSV.node[i];    listSV.node[i] = min;
    
	}
}

void SV_Show_DSTT(PTRSV &FirstSV){
	char malop[15];
	cout<<"Nhap ma lop: ";
	gets(malop);
	DanhSachSV listSV;
	SV_ThemSVVaoDSTT(FirstSV,malop,listSV);
	SV_SapXepTenHo(listSV);
	
	printf("\n       Danh sach sinh vien lop %s: ",malop);
   	printf("\n     STT       MSSV       HO           TEN                PHAI            SDT");
   	for(int i=0; i<listSV.soluong;i++){
   		printf("\n   %5d %10s  %-15s %-10s %5s %15s"   , i+1,listSV.node[i].MASV, listSV.node[i].HO,listSV.node[i].TEN, listSV.node[i].PHAI, listSV.node[i].SDT);
	}
	   
	
}






//===============DS DANG KY================//

int DK_Reccount(PTRDK &FirstDK){
	PTRDK p;
	int tong = 0;
	for(p=FirstDK; p!=NULL; p=p->next){
		++tong;
	}
	return tong;
}

void DK_Insert_last(PTRDK &FirstDK,DangKy dk){
	PTRDK tmp = new nodeDangKy;
	tmp->dangky= dk;
	
	if(FirstDK==NULL){
		tmp->next = FirstDK;
		FirstDK = tmp;
	} 	
	else 
	{
	  PTRDK p = FirstDK;
	  while(p->next!=NULL)
			p = p->next;
	
	   p->next = tmp;
	   tmp->next=NULL;
	}
    
}

PTRDK DK_search_info_masv(PTRDK &First, char *x){
	PTRDK p;
	for(p=First; p!= NULL; p=p->next){
		if(stricmp(p->dangky.MASV,x)==0)
		return p;
	}
	return NULL;
}

int DK_traverse(LIST_LTC &list_ltc, PTRSV &FirstSV)
{
	char huydk[10];
	int malop;
  	cout<<"Nhap ma lop muon xem: ";
  	cin>>malop;
  	int vitri = LTC_Search_theoma(list_ltc,malop);
   	PTRDK p;
   	int stt = 0;
   	p = list_ltc.nodesltc[vitri]->First_DSSVDK; 
   	if(p == NULL){
   		printf("\n   (Khong co sinh vien trong danh sach)");
   		getche();
   		return -1;
   }
      
   	printf("\n       Danh sach lop: ");
   	printf("\n     STT       MSSV       HO           TEN            DIEM        HUY DANG KY");
   	while(p != NULL)
   	{
   		if(p->dangky.HUYDANGKY==false) strcpy(huydk,"");
   		else strcpy(huydk, "Da huy");
   		PTRSV tempsv = SV_search_infosv(FirstSV,p->dangky.MASV);
      	printf("\n   %5d %10s  %-15s %-10s %15d %10s"    , ++stt, p->dangky.MASV, tempsv->sv.HO, tempsv->sv.TEN,p->dangky.DIEM, huydk);
      	p = p->next;
   	}
   getche();
   return vitri;
}
// TIM LOP DUA VAO NIEN KHOA, HOOC KY, MA MON, NHOM
int DK_Search_theo_info(LIST_LTC list_ltc, char *nienkhoa, char *mamon, int hocki, int nhom)
{
	for ( int i =0 ; i <list_ltc.soluong ; i++)
  	     if (stricmp(list_ltc.nodesltc[i]->NIENKHOA,nienkhoa)==0
		   &&stricmp(list_ltc.nodesltc[i]->MAMH,mamon)==0
		   &&list_ltc.nodesltc[i]->HOCKY==hocki
		   &&list_ltc.nodesltc[i]->NHOM==nhom
		   )
		   return i;
	return -1;
}

int DK_InBangDiem(LIST_LTC &list_ltc, PTRSV &FirstSV)
{
	char nienkhoa[10], mamon[10], huydk[10];
	int nhom, hocki;
	
	cout<<"Nhap nien khoa: ";fflush(stdin);
	gets(nienkhoa);
	cout<<"\nNhap ma mon: ";fflush(stdin);
	gets(mamon);
	cout<<"\nNhap hoc ki: ";
	cin>>hocki;
	cout<<"\nNhap nhom: ";
	cin>>nhom;
	
  	int vitri = DK_Search_theo_info(list_ltc,nienkhoa,mamon,hocki,nhom);
  	
   	PTRDK p;
   	int stt = 0;
   	p = list_ltc.nodesltc[vitri]->First_DSSVDK; 
   	if(p == NULL){
   		printf("\n   (Khong co sinh vien trong danh sach)");
   		getche();
   		return -1;
   }
      
   	printf("\n       Danh sach lop: ");
   	printf("\n     STT       MSSV       HO           TEN            DIEM       ");
   	while(p != NULL)
   	{
   		if(p->dangky.HUYDANGKY==false){
   			PTRSV tempsv = SV_search_infosv(FirstSV,p->dangky.MASV);
      		printf("\n   %5d %10s  %-15s %-10s %15d "    , ++stt, p->dangky.MASV, tempsv->sv.HO, tempsv->sv.TEN,p->dangky.DIEM);     	
		}
   		p = p->next;
   	}
   getche();
   return vitri;
}
void DK_SVDangKyLTC(LIST_LTC &list_ltc, char *masv, int malop){
	PTRDK Last,p, tempdk;
  	DangKy dk; 
  	int vitri = LTC_Search_theoma(list_ltc,malop);
  	tempdk=DK_search_info_masv(list_ltc.nodesltc[vitri]->First_DSSVDK,masv);
  	if(tempdk!=NULL){
  		if(tempdk->dangky.HUYDANGKY==false){
  			cout<<"\nSinh vien da dang ky.";
  			return;
		}
		else{
			tempdk->dangky.HUYDANGKY=false;
			cout<<"\n Dang ky thanh cong.";
		}	
	}
  	else{
  		int so_sv_dk = DK_Reccount(list_ltc.nodesltc[vitri]->First_DSSVDK);
  		if(so_sv_dk==list_ltc.nodesltc[vitri]->SOSVMAX){
  			cout<<"\nKhong the dang ky. Lop da day.";
  			return;
		}
		else{
			dk.DIEM = 0;
	  		strcpy(dk.MASV,masv);
	  		dk.HUYDANGKY=false;
	  		p= new nodeDangKy;
	  		p->dangky=dk;
	  		if (list_ltc.nodesltc[vitri]->First_DSSVDK==NULL)
			  list_ltc.nodesltc[vitri]->First_DSSVDK=p;
			else {
			  for (Last = list_ltc.nodesltc[vitri]->First_DSSVDK ; Last->next !=NULL;Last=Last->next);
			  Last->next = p;
			}
			p->next=NULL;	
		} 
		cout<<"\nDang ky thanh cong!";		
	}
}


void DK_HuyDK(LIST_LTC &list_ltc, char *masv, int malop){
	PTRDK tempdk,p;
	int vitri=LTC_Search_theoma(list_ltc,malop);
	tempdk=DK_search_info_masv(list_ltc.nodesltc[vitri]->First_DSSVDK,masv);
	if(tempdk==NULL){
		cout<<"Sinh vien khong co trong lop tin chi.";
		return;
	}
	else{
		tempdk->dangky.HUYDANGKY=true;
		cout<<"\nHuy dang ky thanh cong!";
	}
}

void DK_Sua_theoma(LIST_LTC &list_ltc, PTRSV &FirstSV){
	int vitri=DK_traverse(list_ltc, FirstSV);
	if(vitri==-1) return;
	char maso[10];
	PTRDK p, tempdk;
	do{
		cout<<"\nNhap ma sinh vien muon sua: ";	fflush(stdin);
		gets(maso);
		tempdk = DK_search_info_masv(list_ltc.nodesltc[vitri]->First_DSSVDK,maso);
		if(tempdk==NULL) cout<<"Sinh vien khong co trong lop tin chi.";
	}while(tempdk==NULL);
	PTRSV tempsv = SV_search_infosv(FirstSV,tempdk->dangky.MASV);
	printf("\n   %10s  %-15s %-10s %15d"  , tempdk->dangky.MASV, tempsv->sv.HO, tempsv->sv.TEN,tempdk->dangky.DIEM);
	float diem;
	cout<<"\nNhap diem: ";
	cin>>diem;
	//DK_Search_SV_DSLTC(list_ltc.nodesltc[vitri]->First_DSSVDK,maso)->dangky.DIEM=diem;
}



// SHOW LOP DUA VAO NIEN KHOA, HOC KY
void DK_Show_Lop_theo_hk_nk(PTRMH &root, LIST_LTC list_ltc, char *nienkhoa,  int hocki)
{	int so_sv_dk;
	int so_slot_con_trong;
	PTRMH p;
	printf ("                     DANH SACH LOP TIN CHI HOC KY %d, NIEN KHOA %s\n",hocki, nienkhoa);
	printf ("  Malop     Ma mon       Ten mon       Nhom       So SV da dang ky      So slot con trong      \n");
	for ( int i =0 ; i <list_ltc.soluong ; i++)
  	    if (stricmp(list_ltc.nodesltc[i]->NIENKHOA,nienkhoa)==0 && list_ltc.nodesltc[i]->HOCKY==hocki ){
  	     	p=MH_SearchMS(root, list_ltc.nodesltc[i]->MAMH);
  	     	so_sv_dk = DK_Reccount(list_ltc.nodesltc[i]->First_DSSVDK);
  	     	so_slot_con_trong = list_ltc.nodesltc[i]->SOSVMAX - so_sv_dk;
		  	printf ("%8d %15s  %-15s  %-8d    %5d   %5d    \n", 
				  list_ltc.nodesltc[i]->MALOPTC,
				  list_ltc.nodesltc[i]->MAMH,
				  p->mh.TENMH,
				  list_ltc.nodesltc[i]->NHOM,
				  so_sv_dk,
				  so_slot_con_trong);  
	}
}



// nien khoa, hoc ki, ma mon , nhom
int DK_Show_theo_info(LIST_LTC &list_ltc, PTRSV &FirstSV)
{
	char nienkhoa[10], mamon[10], huydk[10];
	int nhom, hocki;
	
	cout<<"Nhap nien khoa: ";fflush(stdin);
	gets(nienkhoa);
	cout<<"\nNhap ma mon: ";fflush(stdin);
	gets(mamon);
	cout<<"\nNhap hoc ki: ";
	cin>>hocki;
	cout<<"\nNhap nhom: ";
	cin>>nhom;
	
  	int vitri = DK_Search_theo_info(list_ltc,nienkhoa,mamon,hocki,nhom);
   	PTRDK p;
   	int stt = 0;
   	p = list_ltc.nodesltc[vitri]->First_DSSVDK; 
   	if(p == NULL){
   		printf("\n   (Khong co sinh vien trong danh sach)");
   		getche();
   		return -1;
   }
      
   	printf("\n       Danh sach lop: ");
   	printf("\n     STT       MSSV       HO           TEN          PHAI		SDT			MALOP        HUY DANG KY");
   	while(p != NULL)
   	{
   		if(p->dangky.HUYDANGKY==false) strcpy(huydk,"");
   		else strcpy(huydk, "Da huy");
   		PTRSV tempsv = SV_search_infosv(FirstSV,p->dangky.MASV); 		
      	printf("\n   %5d %10s  %-15s %-10s %-5s %-15s %-15s %-10s"   , ++stt, p->dangky.MASV, tempsv->sv.HO, tempsv->sv.TEN,tempsv->sv.PHAI,tempsv->sv.SDT,tempsv->sv.MALOP, huydk);
      	p = p->next;
   	}
   getche();
   return vitri;
}

// DANG KY LOP TIN CHI - NHAP MA SV
void DK_DangKyLopTinChi(PTRMH &root, PTRSV &FirstSV, LIST_LTC &list_ltc){
	char masv[15], nienkhoa[10];
	int hocki, malop, chon;
	PTRSV p;
	cout<<"Nhap ma sinh vien: ";fflush(stdin);
	gets(masv);
	p=SV_search_infosv(FirstSV,masv);
	if(p==NULL){
		cout<<"\nSinh vien khong ton tai.";
		return;
	}
	printf("\n        MSSV       HO           TEN            MA LOP          PHAI            SDT");
	printf("\n   %10s  %-15s %-10s %15s %5s %15s"   , p->sv.MASV, p->sv.HO,p->sv.TEN, p->sv.MALOP, p->sv.PHAI, p->sv.SDT);
	cout<<"\nNhap nien khoa: ";fflush(stdin);
	gets(nienkhoa);
	cout<<"\nNhap hoc ky: ";
	cin>>hocki;
	DK_Show_Lop_theo_hk_nk(root,list_ltc, nienkhoa, hocki);
	do{
		cout<<"\n\t\t    1. Dang ky\n";
		cout<<"\t\t    2. Huy dang ky\n";
		cout<<"\t\t    3. Thoat\n";
		cout<<"Chon: ";
		cin>>chon;
		switch(chon){
			case 1: {
				cout<<"\n NHAP MA LOP 0 DE DUNG DANG KY";
				do{
					cout<<"\nNhap ma lop muon dang ky: ";
					cin>>malop;
					if(malop==0) break;
					if(stricmp(list_ltc.nodesltc[malop-1]->NIENKHOA,nienkhoa)==0 && list_ltc.nodesltc[malop-1]->HOCKY==hocki){
						DK_SVDangKyLTC(list_ltc,masv,malop);
					}else cout<<"Lop khong co trong nien khoa "<<nienkhoa<< " hoc ky "<<hocki;
				}while(true);
				break;
			}
			case 2: {
				cout<<"\n NHAP MA LOP 0 DE DUNG LAI";
				do{
					cout<<"\nNhap ma lop muon huy dang ky: ";
					cin>>malop;
					if(malop==0) break;
					if(stricmp(list_ltc.nodesltc[malop-1]->NIENKHOA,nienkhoa)==0 && list_ltc.nodesltc[malop-1]->HOCKY==hocki){
						DK_HuyDK(list_ltc,masv,malop);
					}else cout<<"Lop khong co trong nien khoa "<<nienkhoa<< " hoc ky "<<hocki;
				}while(true);
				break;
			}
			case 3:{
				
				return;
			}
		}
	}while(1);	
}

void LTC_Show_HuyLop(LIST_LTC &list_ltc, char *nienkhoa, int hocky){
	int sosvdk, stt=0;
	printf ("                DANH SACH LOP TIN CHI CO SO SV DK NHO HON SO SV MIN \n");
 	printf ("  Stt   Ma lop   Ma mon   Nhom   Nien khoa     Hoc Ky    So sv max     So sv min   \n");
	for(int i=0;i<list_ltc.soluong;i++){		
		if(stricmp(list_ltc.nodesltc[i]->NIENKHOA,nienkhoa)==0 && list_ltc.nodesltc[i]->HOCKY==hocky){
			sosvdk=DK_Reccount(list_ltc.nodesltc[i]->First_DSSVDK);
			if(sosvdk<list_ltc.nodesltc[i]->SOSVMIN)
				printf ("%8d %5d  %-10s  %-8d  %10s  %5d  %5d   %5d    \n", 
				  stt++,
				  list_ltc.nodesltc[i]->MALOPTC,
				  list_ltc.nodesltc[i]->MAMH,
				  list_ltc.nodesltc[i]->NHOM,
				  list_ltc.nodesltc[i]->NIENKHOA,
				  list_ltc.nodesltc[i]->HOCKY,
				  list_ltc.nodesltc[i]->SOSVMAX,
				  list_ltc.nodesltc[i]->SOSVMIN);
		}	
	}
}

void LTC_HUY(LIST_LTC &list_ltc, char *nienkhoa, int hocky){
	int sosvdk;
	for(int i=0;i<list_ltc.soluong;i++){		
		if(stricmp(list_ltc.nodesltc[i]->NIENKHOA,nienkhoa)==0 && list_ltc.nodesltc[i]->HOCKY==hocky){
			sosvdk=DK_Reccount(list_ltc.nodesltc[i]->First_DSSVDK);
			if(sosvdk<list_ltc.nodesltc[i]->SOSVMIN)
			list_ltc.nodesltc[i]->HUYLOP=true;
		}
	}
}

void LTC_HuyLop(LIST_LTC &list_ltc){
	char nienkhoa[10];
	int hocky;
	cout<<"\nNhap nien khoa: "; fflush(stdin);
	gets(nienkhoa);
	cout<<"\nNhap hoc ky: ";
	cin>>hocky;
	LTC_Show_HuyLop(list_ltc,nienkhoa,hocky);
	int yn = XacNhan("\nBan co muon huy cac lop nay khong? (Y/N): ");
	if(yn==1){
		LTC_HUY(list_ltc, nienkhoa,hocky);
		cout<<"\nHuy thanh cong";
	}
	
	
}

// menu 
char menu(){
	int chucnang;
	do {
		printf("\n\n\t\tQUAN LY SINH VIEN THEO HE TIN CHI");
		printf("\n\Cac chuc nang cua chuong trinh\n");
		printf("   1. Tao danh sach sinh vien\n");
		printf("   2: Xem danh sach sinh vien\n");
		printf("   3: Nhap mon hoc\n");
		printf("   4: Xem danh sach mon hoc\n");
		printf("   14: Xoa MH \n");
		printf("   15: Sua MH \n");
		printf("   16: Sap xep MH the ten \n");
		printf("   5: Tao lop tin chi\n");
		printf("   6: Xem lop tin chi\n");
		printf("   7: Xoa lop tin chi\n");
		printf("   8: Sua lop tin chi\n");
		printf("   9: Them lop tin chi\n");
		printf("   10: Them SV vao lop\n");
		printf("   11: Show DSSV LTC theo ma lop\n");
		printf("   18: Show DSSV cua lop theo ten ho\n");
		printf("   12: Xoa SV trong lop\n");
		printf("   13: Sua SV theo lop\n");
		printf("   17: Show DSSV LTC theo info\n");
		printf("   19: Dang ky lop tin chi\n");
		printf("   20: Ghi vao file \n");
      	printf("   21: Mo danh sach \n");
      	printf("   22: Huy lop tin chi \n");
		printf("Chuc nang ban chon: ");
		cin>>chucnang;
		
	}while(chucnang < 0) ;
      return chucnang;
}

int main(){
	PTRMH treeMH = NULL;
	LIST_LTC list_ltc;
	list_ltc.soluong =0;
	PTRSV FirstSV = NULL;
		
	do {
		system("cls");
      	int chucnang = menu();
      	system("cls");
      	fflush(stdin);
      	switch(chucnang){
      		case 1:
      			{
      			SV_Create_DSSV(FirstSV);
      			break;
			}
			case 2:{
				SV_traverse(FirstSV);
				break;
			}
			case 3:{
				MH_Create(treeMH);
				break;
			}
			case 4:{
				printf("\n       Danh sach mon hoc: ");
   				printf("\n     Ma mon       Ten mon    STCLT	STCTH"); 
				MH_Show(treeMH);	
				getch();
				break;
			}
			case 5:{
				Create_List_LTC(list_ltc,treeMH);
				break;
			}
			case 6:{
				LTC_traverse(list_ltc);
				break;
			}
			case 7 :{
				LTC_Delete_theoma(list_ltc);
				break;
			}
			case 8:{
				LTC_Sua_theoma(list_ltc,treeMH);
				break;
			}
			case 9:{
				Create_List_LTC(list_ltc,treeMH);
				break;
			}
			case 10:{
				SV_Them_SV_theo_malop(FirstSV);
				break;
			}
			case 11:{
				DK_traverse(list_ltc,FirstSV);
				break;
			}
			case 12:{
				SV_Xoa_SV_theo_malop(FirstSV);
				break;
			}
			case 13:{
				SV_Sua_SV_theo_malop(FirstSV);
				break;
			}
			case 14:{
				MH_Delete(treeMH);
				break;
			}
			case 15:{
				MH_Sua(treeMH);
				break;
			}
			case 16:{
				MH_SapXep(treeMH);
				break;
			}
			case 17:{
				DK_Show_theo_info(list_ltc, FirstSV);
				break;
			}
			case 18:{
				SV_Show_DSTT(FirstSV);
				getch();
				break;
			}
			case 19:{
				DK_DangKyLopTinChi(treeMH,FirstSV, list_ltc);
				getch();
				break;
			}
			case 20:{
				MH_ghiFileMonHoc(treeMH);
				SV_SaveFile(FirstSV);
				LTC_ghiFile(list_ltc);
				break;
			}
			case 21: {
				MH_docFileMonHoc(treeMH);
				SV_OpenFile(FirstSV);
				LTC_docFile(list_ltc);
				getch();
				break;
			}
			case 22:{
				LTC_HuyLop(list_ltc);
				getch();
				break;
			}
			
		}
	}
	while(1);
	
}









