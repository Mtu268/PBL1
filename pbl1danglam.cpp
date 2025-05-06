#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>

#define TRUE 1
#define FALSE 0
#define INVALID_BOOK_ID -1

struct Book {
	int Id;
	char bookName [100] , Author[100], Publisher[100];
	int publishYear;
	int used;
	int status; //Br ó th? là "Book Reserved" (sách dang du?c mu?n ho?c d?t tru?c), ho?c m?t bi?n ph? d? dánh d?u tr?ng thái nào dó trong chuong trình (tùy b?n quy d?nh).
    int Amount;
} ;

typedef struct Book book;

struct BookNode {
	book data;
	struct BookNode *next;
} ;

typedef struct BookNode *Node;

Node createEmptyList();
book handleLineData(char *line);
Node readData(Node head);
Node Createbooknode(book b);
book createBook();
Node insertFirst(Node head, book New_data);    
Node insertLast(Node head, book New_data);
Node insertAfter(Node head, int id);
Node insert_Book(Node head);
Node delFirst(Node head); 
Node delLast(Node head); 
Node delId(Node head);
Node delAfter(Node head);
Node delBookName(Node head);
Node delAuthor(Node head);
Node del_Book(Node head);
void findBookName(Node head);
void findAuthor(Node head);
void findPublisher(Node head);
int find_Book(Node head);
void display(Node p);
void displayall(Node head);
void displayAvailable(Node head);
void displayNotAvailable(Node head);
Node split(Node head);
Node mergeByBookName(Node first, Node second);
Node mergeByAuthor(Node first, Node second);
Node mergeByPublisher(Node first, Node second);
Node mergeByPublishYear(Node first, Node second);
Node mergeSort(Node head, int mode);
int display_Book(Node head);
Node borrow(Node head);
Node giveback(Node head);
Node borrow_giveback_Book(Node head);
Node fixId(Node head);
Node fixBookName(Node head);
Node fixAuthor(Node head);
Node fixPublisher(Node head);
Node fixPublishYear(Node head);
Node fixUsed(Node head);
Node fixAmount(Node head);
Node fix_Book(Node head);
Node writeData(Node head);

int main() {
	int choice;
	Node head = createEmptyList();
	
	do {
		system("cls");
		printf("\n -*-*-*-*-*-*-*-*-*-*-*-*-*-QUAN LY SACH TRONG THU VIEN-*-*-*-*-*-*--*-*-*-*-*-*-* \n");
		printf("\n ====================================MENU==================================== \n");
	    printf("\n 1.Khoi tao danh sach . \n");
	    printf("\n 2.Them mot cuon sach vao danh sach. \n");
	    printf("\n 3.Xoa mot cuon sach khoi danh sach. \n");
	    printf("\n 4.Tim kiem sach. \n");
	    printf("\n 5.Chuc nang xem danh sach. \n");
	    printf("\n 6.Chuc nang muon/tra sach \n");
	    printf("\n 7.Chuc nang chinh sua noi dung sach. \n");
	    printf("\n 8.Chuc nang luu file. \n");
	    printf("\n 0.Thoat. \n ");
	    printf("\n =============================================================================== \n ");
	    printf("Nhap chuc nang: ");
	    scanf("%d",&choice);
	    getchar();//doc 1 ki tu tu ban phim
	    switch(choice)
	    {
	    	case 1:
	    		head = readData(head);
	    		break;
	    	case 2:
	    		head = insert_Book(head);
	    		break;
	    	case 3:
	    		head = del_Book(head);
	    		break;
	    	case 4:
	    		find_Book(head);
	    		break;
	    	case 5:
	    		display_Book(head);
	    		break;
	    	case 6:
	    		head = borrow_giveback_Book(head);
	    		break;
	    	case 7:
	    		head = fix_Book(head);
	    		break;
	    	case 8:
	    		head = writeData(head);
	    		break;
	    	case 0:
	    		printf("Thoat. \n");
	    	    getch();
	    	    return 0;
	    	default : 
	    	    printf(" Khong co chuc nang nay. \n");
	    	   	printf(" Hay chon chuc nang khac. \n");
			    printf(" Nhap phim bat ki. \n");
			    getch();
	    	    break;
	}  		       
		
	}while (choice != 0);
	return 0;
	
}
//khoi tao danh sach rong
Node createEmptyList(){
	return NULL;
}

//ham tach cac thanh phan cua 1 dong file
book handleLineData(char *line) {
    book b;
    b.Id = INVALID_BOOK_ID;

    char *tmp;
    tmp = strtok(line, ",");
    if (tmp == NULL) {
        printf("Du lieu khong dung dinh dang: %s", line);
        exit(EXIT_FAILURE);
    }

    b.Id = atoi(tmp);  

    if (b.Id == 0 && strcmp(tmp, "0") != 0) {  
        printf("Loi: ID khong phai so hop le: %s\n", tmp);
        exit(EXIT_FAILURE);
    }

    int index = 0;
    while ((tmp = strtok(NULL, ",")) != NULL) {
        switch (index) {
            case 0:
                strcpy(b.bookName, tmp);
                break;
            case 1:
                strcpy(b.Author, tmp);
                break;
            case 2:
                strcpy(b.Publisher, tmp);
                break;
            case 3:
                b.publishYear = atoi(tmp);  
                
                break;
            case 4:
                b.used = atoi(tmp); 
                
                break;
            case 5:
                b.Amount = atoi(tmp);  
                break;
            default:
                printf("Du lieu co qua nhieu truong: %s", line);
                exit(EXIT_FAILURE);
        }
        index++;
    }
    b.status = 0;
    return b;
}

Node readData(Node head){
	 char fileName [50];
	 printf("Nhap ten file : ");
	 fgets(fileName,sizeof(fileName),stdin);
	 fileName[strlen(fileName)-1]='\0';
	 
	 FILE *f= fopen (fileName,"r");
	 	if(f == NULL){
		printf("Co loi khi mo file : %s\n", fileName);
		getch();
		return head;
	}
	char line[500];
	while(fgets(line, sizeof(line), f)){
		book b = handleLineData(line);
	if (b.Id != INVALID_BOOK_ID) {
            head = insertLast(head, b);
        }
	}
	fclose (f);
	getch();
	return head;
	
}

//tao mot 1 node trong BookNode
Node Createbooknode(book b){
	Node p;
	p = (Node)malloc(sizeof(struct BookNode));
	p->data= b;
	p->next= NULL;
	return p;
}


//nhap thong tin moi quyen sach
book createBook(){
	book newBook;
	printf("Nhap ma so sach: ");
	scanf("%d",&newBook.Id);
	getchar(); // xoa '\n' sau scanf
	
	printf("Nhap ten sach:");
	fgets(newBook.bookName,sizeof(newBook.bookName),stdin);
	newBook.bookName[strlen(newBook.bookName)-1]='\0';
	
    printf("Nhap ten tac gia: ");
	fgets(newBook.Author,sizeof(newBook.Author),stdin);
	newBook.Author[strlen(newBook.Author)-1]='\0';
    
	printf("Nhap nha xuat ban: ");
	fgets(newBook.Publisher,sizeof(newBook.Publisher),stdin);
	newBook.Publisher[strlen(newBook.Publisher)-1]='\0';
	
	printf("Nhap nam xuat ban:");
	scanf("%d",&newBook.publishYear);
//	getchar(); // xoa '\n' sau scanf
	
	printf("Nhap so lan muon sach:");
	scanf("%d",&newBook.used);
	//getchar(); // xoa '\n' sau scanf
	
	printf("Nhap so luong sach:");
	scanf("%d",&newBook.Amount);
//	getchar(); // xoa '\n' sau scanf
	
	newBook.status = 0;
	return newBook;
}

//them dau 
Node insertFirst(Node head, book New_data) {
    Node tmp = Createbooknode(New_data); 
    if (head == NULL) {
        head = tmp;
    } else {
        tmp->next= head;  
        head = tmp;       
    }
    return head;  
}


//them cuoi
Node insertLast(Node head, book New_data){
    Node tmp = Createbooknode(New_data);
    if(head == NULL ){
    	head = tmp;
	}else{
		Node p = head;
	    while(p->next!= NULL){
	    	p=p->next;
		}
		p->next = tmp;
	}
	return head;
}

//them vao sau mot cuon sach
Node insertAfter(Node head, int id){
	
	if(head == NULL){
		printf("Danh sach dang rong. Sach moi se duoc them vao dau.\n");
		book New_data = createBook();
		head = insertFirst(head,New_data);
		return head;
	}
	
	    Node curr = head;
	while (curr != NULL && curr->data.Id != id){
		curr = curr -> next;
	}  
	 if (curr == NULL) {
        printf("Khong tim thay sach co ID = %d. Khong the chen sau.\n", id);
        return head; 
    }
    book New_data= createBook();
    Node tmp = Createbooknode(New_data);
    
    tmp->next=curr->next;
    curr->next= tmp;
    
    return head;
	
}

//tao danh sach chen
Node insert_Book(Node head){
	int choice, id;
    while (TRUE){
    	system("cls");
    	printf("\n -*-*-*-*-*-*-*-*-*-* -*-*-*-*-*-*-*-*-*-*Them sach moi -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* \n");
    	printf("\n 1.Them vao dau danh sach. \n");
    	printf("\n 2.Them vao cuoi danh sach. \n");
    	printf("\n 3.Them vao sau mot cuon sach nao do. \n");
    	printf("\n 0.Thoat. \n ");
	    printf("\n =============================================================================== \n ");
	    printf("Nhap chuc nang : ");
	    scanf("%d", &choice);
	    switch(choice){
	    	case 1: 
	    	    head = insertFirst(head,createBook());
	    	    break;
	        case 2:
	        	head = insertLast(head,createBook());
	        	break;
	        case 3: 
	            printf("Nhap vi tri sau id can them sach :");
	            scanf("%d", &id);
	            head=insertAfter(head,id);
	            break;
	        case 0:
	        	printf("Thoat chuc nang. \n");
	        	getch();
	            return head;
	        
	        default:
	        	printf("khong co chuc nang nay. xin vui long chon chuc nang khac.\n");
	        	printf("Nhap phim bat ki \n");
	        	getch();
	        	break;
			
		}
		getch();	
	}
	return head;
}

//xoa cuon sach o dau danh sach
Node delFirst(Node head){
	if(head == NULL){
		printf("khong xoa duoc gi ca !");
		return NULL;
	}
    
    Node tmp = head;
    head = head->next;
    free(tmp);
    
    return head;
}

Node delLast( Node head){
	if( head == NULL || head->next == NULL){
		return delFirst(head);
	}

    Node p = head;
	while (p->next->next != NULL){
		p = p->next;
	}
	free(p->next);
	
	p->next = NULL;
	
	return head;
}

//xoa sach theo ma so
Node delId(Node head){
	int id;
	printf("nhap ma so sach can xoa: ");
	scanf("%d", &id);
	  if(head == NULL || head->data.Id == id){
	  	return delFirst(head);
	  }
   else {
   	
   Node p = head;
   while(p->next != NULL){
   	   if(p->next->data.Id == id){
   	   	Node tmp = p->next;
   	   	p ->next = p->next->next;
   	   	free(tmp);
   	   	printf("da xoa sach co ID %d.\n",id);
   	   	return head;
		  }
		  p=p->next;
   }
}
   printf("Khong tim thay vi tri nay !!! ");
   return head;
	
}

//xoa cuon sach o sau cuon sach co id nao do
Node delAfter(Node head, int id) {
   if (head == NULL) {
        printf("Danh sach rong. Khong co gi de xoa.\n");
        return head;
    }
   else {
    Node p = head;
    while (p != NULL) {
        if (p->data.Id == id) {
            if (p->next == NULL) {
                printf("Khong co Node nao sau ID = %d de xoa.\n", id);
                return head;
            }

            // Xoa node sau p
            Node temp = p->next;
            p->next = temp->next;
            free(temp);
            printf("Da xoa sach sau ID = %d.\n", id);
            return head;
        }
        p = p->next;
    }
}

    printf("Khong tim thay sach co ID = %d.\n", id);
    return head;
}

//xoa ten sach
Node delBookName(Node head){
	char bookname[100];
	printf("nhap ten sach can xoa: ");
	fgets(bookname,sizeof(bookname),stdin);
	bookname[strlen(bookname)-1]='\0';
	
	if(head == NULL ||strcmp(strupr(head->data.bookName),strupr(bookname)) == 0){
		head = delFirst(head);
		return head;
	}
	
	
	Node p = head;
		while(p ->next != NULL){
			if(strcmp(strupr(p->next->data.bookName), strupr(bookname)) == 0){
				Node tmp = p->next;
				p->next=tmp->next;
				free(tmp);
   	   	        return head; //ket thuc som neu da xoa
   	     	} 
   	     	p=p->next;
		} 
		
		
		printf("khong co ten sach trong thu vien !!!");
        return head;	
}

//xoa ten tac gia
Node delAuthor(Node head){
	char author[100];
	printf("nhap ten tac gia can xoa:");
	fgets(author,sizeof(author),stdin);
	author[strlen(author)-1]='\0';
	
    if (head == NULL)
    {
        head = delFirst(head);
    }
    else
    {
    if(strcmp(strupr(head->data.Author), strupr(author)) == 0) 
    {
        while (strcmp(strupr(head->data.Author), strupr(author)) == 0)
                {
                    head = head->next;
                }
    }
    int found = 1;
    for (Node p = head; p->next != NULL; p = p->next)
    {
        if (strcmp(strupr(p->next->data.Author), strupr(author)) == 0)
        {
            while(strcmp(strupr(p->next->data.Author), strupr(author)) == 0)
            {
                p->next = p->next->next;
                found = 0;
            }
        }
    }
    if (found)
    {
        printf("Khong co ten tac gia nay trong thu vien !!! ");
    }
    }
    return head;

}


Node del_Book(Node head){
	int choice;
	while(TRUE){
		system("cls");
     	printf("\n -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*Xoa sach-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* \n");
     	printf("\n 1.Xoa cuon sach o dau danh sach. \n");
     	printf("\n 2.Xoa cuon sach o cuoi danh sach. \n");
     	printf("\n 3.Xoa cuon sach theo ma so. \n");
     	printf("\n 4.Xoa cuon sach o sau cuon sach co ma so nao do. \n");
     	printf("\n 5.Xoa cuon sach theo ten sach. \n");
     	printf("\n 6.Xoa cuon sach theo ten tac gia. \n");
     	printf("\n 0.Thoat \n");
     	printf("\n =============================================================================== \n ");
	    printf("Nhap chuc nang : ");
	    scanf("%d", &choice);
	    getchar();
	    switch (choice){
	    	case 1:
	    		head = delFirst(head);
	    		break;
	    	case 2: 
	    	    head = delLast(head);
	    	    break;
	    	case 3: 
	    	    head = delId(head);
	    	    break;
	    	case 4:
	    		int id;
	    		printf("nhap id: ");
	    		scanf("%d", &id);
	    		head = delAfter(head,id);
	    		break;
	    	case 5:
	    		head = delBookName(head);
	    		break;
	    	case 6:
	    		head = delAuthor(head);
	    		break;
	    	case 0:
	        	printf("Thoat chuc nang. \n");
	        	getch();
	            return head;
	        
	        default:
	        	printf("khong co chuc nang nay. xin vui long chon chuc nang khac.\n");
	        	printf("Nhap phim bat ki \n");
	        	getch();
	        	break;
		}
		getch();
	}
	return head;
}


// Tìm kiem sách theo tên sách
void findBookName(Node head) {
    char bookname[100];
    printf("Nhap ten sach can tim: \n"); 
    fgets(bookname, sizeof(bookname), stdin);
    bookname[strlen(bookname)-1]='\0';
       
    printf("Danh sach hien tai:\n");
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("%10s%40s%25s%20s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So lan muon", "So luong");
    Node p = head;
    while (p != NULL) {
        if (strcmp(strupr(p->data.bookName), strupr(bookname)) == 0) {
            display(p);
        }
        p = p->next;
    }
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
}

// Tìm kiem sách theo tên tác gia
void findAuthor(Node head) {
    char author[100];
    printf("Nhap ten tac gia can tim: \n");
    fgets(author, sizeof(author), stdin);
    author[strlen(author)-1]='\0';

    printf("Danh sach hien tai:\n");
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("%10s%40s%25s%20s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So lan muon", "So luong");
    Node p = head;
    while (p != NULL) {
        if (strcmp(strupr(p->data.Author), strupr(author)) == 0) {
            display(p);
        }
        p = p->next;
    }
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
}

// Tìm ki?m sách theo nhà xuat ban
void findPublisher(Node head) {
    char publisher[100];
    printf("Nhap ten nha xuat ban can tim: \n");
    fgets(publisher, sizeof(publisher), stdin);
    publisher[strlen(publisher)-1]='\0';
    printf("Danh sach hien tai:\n");
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("%10s%40s%25s%20s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So lan muon", "So luong");
    Node p = head;
    while (p != NULL) {
        if (strcmp(strupr(p->data.Publisher), strupr(publisher)) == 0) {
            display(p);
        }
        p = p->next;
    }
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
}

int find_Book(Node head){
	int choice;
	while(TRUE){
		system("cls");
		printf("\n -*-*-*-*-*-*-*-*-*-*Tim sach-*-*-*-*-*-*-*-*-*-* \n");
	    printf("\n 1.Tim theo ten sach. \n");
        printf("\n 2.Tim theo ten tac gia. \n");
        printf("\n 3.Tim theo ten nha xuat ban. \n");
        printf("\n 0.Thoat. \n");
        printf("\n =============================================================================== \n ");
        printf("Nhap lua chon : ");
        scanf("%d", &choice);
        getchar();
        switch(choice){
        	case 1:
        		findBookName(head);
        		break;
        	case 2:
        		findAuthor(head);
        		break;
        	case 3:
        		findPublisher(head);
				break;
			case 0:
	        	printf("Thoat chuc nang. \n");
	        	getch();
	            return 0;
	        
	        default:
	        	printf("khong co chuc nang nay. xin vui long chon chuc nang khac.\n");
	        	printf("Nhap phim bat ki \n");
	        	getch();
	        	break;
			}
			getch();
		} 
}

void display(Node p){
	printf("%10d%40s%25s%20s%16d%20d%15d\n", p->data.Id, p->data.bookName,p->data.Author,p->data.Publisher,p->data.publishYear,p->data.used,p->data.Amount);
}

//hien thi danh sach all
void displayall(Node head){
	if(head == NULL){
		printf("danh sach rong, khong hien thi sach duoc !!\n");
		return;
	} else {
	printf("Danh sach hien tai:\n");
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("%10s%40s%25s%20s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So lan muon","So luong");
    Node p = head;
    while ( p != NULL){
    	display(p);
    	p=p->next;
	}
 }
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");	
}

//hien thi danh sach chua cho muon
void displayAvailable(Node head){
	printf("Danh sach hien tai:\n");
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("%10s%40s%25s%20s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So lan muon","So luong");
    Node p = head;
    while ( p != NULL){
    	if(p->data.Amount >0){
    	display(p);
    }
    	p=p->next;
	}
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");	
}

//hien thi cuon sach dang cho muon
void displayNotAvailable(Node head){
		printf("Danh sach hien tai:\n");
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("%10s%40s%25s%20s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So lan muon","So luong");
    Node p = head;
    while ( p != NULL){
    	if(p->data.Amount == 0){
    	display(p);
    }
    	p=p->next;
	}
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");	
}

//ham tach danh sach thanh 2 nua
Node split(Node head){
	Node fast = head;
	Node slow = head;
	
	while (fast != NULL && fast->next != NULL ){
		fast= fast->next->next;
		if(fast != NULL)
		   slow =slow ->next;
	}
	Node temp = slow->next;
	slow->next = NULL;
	return temp;
}

//sap xep theo van alphabet ten sach
Node mergeByBookName(Node first, Node second){
	if (first == NULL) return second;
    if (second == NULL) return first;
    
    if(strcmp(first->data.bookName, second->data.bookName)<0){
    	first->next =  mergeByBookName(first->next, second);
    	return first;
	}else{
		second->next =  mergeByBookName(first,second->next);
		return second;
	}
}

//sap xep theo van alphabet ten tac gia
Node mergeByAuthor(Node first, Node second){
	if (first == NULL) return second;
    if (second == NULL) return first;
    
    if(strcmp(first->data.Author, second->data.Author)<0){
    	first->next =  mergeByAuthor(first->next, second);
    	return first;
	}else{
		second->next =  mergeByAuthor(first,second->next);
		return second;
	}
}

//sap xep theo van alphabet ten nha san xuat
Node mergeByPublisher(Node first, Node second){
	if (first == NULL) return second;
    if (second == NULL) return first;
    
    if(strcmp(first->data.Publisher, second->data.Publisher)<0){
    	first->next =  mergeByPublisher(first->next, second);
    	return first;
	}else{
		second->next =  mergeByPublisher(first,second->next);
		return second;
	}
}

//sap xep sach duoc xuat ban moi nhat (theo nam)
Node mergeByPublishYear(Node first, Node second){
	if (first == NULL) return second;
    if (second == NULL) return first;
    
   if (first->data.publishYear > second->data.publishYear){
    	first->next =  mergeByPublishYear(first->next, second);
    	return first;
	}else{
		second->next =   mergeByPublishYear(first,second->next);
		return second;
	}
}


//ham gop ca 2 nua da sap xep
Node mergeSort(Node head, int mode){
	if (head == NULL || head->next == NULL) {
        return head;
    }
    Node second = split(head);
    
    head = mergeSort(head,mode);
    second = mergeSort(second, mode);
    
    switch(mode){
    	case 1: 
           	return mergeByBookName(head, second);
    	case 2:
    		return mergeByAuthor(head, second);
    	case 3:
    		return mergeByPublisher(head, second);
    	case 4:
    		return mergeByPublishYear(head, second);
    	default:
    		return NULL;
	}
}

int display_Book(Node head) {
    int  choice;
    while (TRUE) {
        system("cls");
        printf("\n -*-*-*-*-*-*-*-*-*-*Xem danh sach-*-*-*-*-*-*-*-*-*-* \n");
        printf("\n 1.Xem toan bo danh muc sach. \n");
        printf("\n 2.Xem sach dang cho muon . \n");
        printf("\n 3.Xem sach chua cho muon  . \n");
        printf("\n 4.Xem theo thu tu alphabet cua ten sach. \n");
        printf("\n 5.Xem theo thu tu alphabet cua ten tac gia. \n");
        printf("\n 6.Xem theo thu tu alphabet cua ten nha xuat ban. \n");
        printf("\n 7.Xem theo thu tu sach xuat ban moi nhat. \n");
        printf("\n 0.Thoat. \n");
        printf("\n =============================================================================== \n ");
        printf("Nhap lua chon : ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                displayall(head);
                break;
            case 2:
                displayNotAvailable(head);
                break;
            case 3:
                displayAvailable(head);
                break;
            case 4:
                head = mergeSort(head, 1); // sort theo ten sach
                displayall(head);
                break;
            case 5:
                head = mergeSort(head, 2); // sort theo tac gia
                displayall(head);
                break;
            case 6:
                head = mergeSort(head, 3); // sort theo nha xuat ban
                displayall(head);
                break;
            case 7:
                head = mergeSort(head, 4); // sort theo nam san suat
                displayall(head);
                break;
            case 0:
                printf(" Ban da thoat chuc nang nay. \n");
                getch();
                return 0;
            default:
	        	printf("khong co chuc nang nay. xin vui long chon chuc nang khac.\n");
	        	printf("Nhap phim bat ki \n");
                getch();
                system("cls");
                break;
        }
        getch();
    }
}

//muon sach
Node borrow(Node head){
	displayAvailable ( head);
	int BookId,Quantity;
	int found =0;
	printf("nhap ma so sach can nhan :\n");
	scanf("%d",&BookId);
	printf("Nhap so luong sach can muon: ");
    scanf("%d", &Quantity);
    
Node p = head;
    while (p != NULL) {
        if (p->data.Id == BookId) {
            found = 1;
            if (p->data.Amount >= Quantity) {
                p->data.Amount -= Quantity;
                p->data.used += 1;
                p->data.status += Quantity;
                printf("Muon sach thanh cong!\n");
            } else {
                printf("Khong du sach de muon! Chi con %d cuon.\n", p->data.Amount);
            }
            break;
        }
        p = p->next;
    }
	if(found == 0) printf("Khong tim thay ma so sach nay trong thu vien sach chua cho muon!!! \n");
    return head;
}

Node giveback(Node head){
	int BookId,Quantity;
	int found =0;
	printf("nhap ma so sach can nhan :\n");
	scanf("%d",&BookId);
    printf("Nhap so luong sach can tra: \n ");
    scanf("%d", &Quantity);
 Node p = head;
    while (p != NULL) {
        if (p->data.Id == BookId) {
            found = 1;
            if (p->data.status >= Quantity) {
                p->data.Amount += Quantity;
                p->data.status -= Quantity;
                printf("Tra sach thanh cong!\n");
            } else {
                printf("So luong tra vuot qua so luong da muon! Chi co %d cuon dang duoc muon.\n", p->data.status);
            }
            break;
        }
        p = p->next;
    }

	if(found == 0) printf("Khong tim thay ma so sach nay trong thu vien sach chua cho muon!!! \n");
    return head;
}

Node borrow_giveback_Book(Node head){
	int choice;
	while(TRUE){
		system("cls");
	    printf("\n -*-*-*-*-*-*-*-*-*-*Muon/tra sach-*-*-*-*-*-*-*-*-*-* \n");
	    printf("\n 1.Muon sach. \n");
	    printf("\n 2.Tra sach. \n");
	    printf("\n 0.Thoat \n");
	    printf("\n =============================================================================== \n ");
        printf("Nhap lua chon : ");
        scanf("%d", &choice);
        switch(choice){
        	case 1:
        		head = borrow(head);
        		break;
        	case 2:
        		head = giveback(head);
        		break;
        		case 0:
	        	printf("Thoat chuc nang. \n");
	        	getch();
	            return head;
	        
	        default:
	        	printf("khong co chuc nang nay. xin vui long chon chuc nang khac.\n");
	        	printf("Nhap phim bat ki \n");
	        	getch();
	        	break;
		}
		getch();
	}
	return head;
}

Node fixId(Node head){
	int BookId;
	int found = 0;
	printf("nhap ma so sach can nhan :\n");
	scanf("%d",&BookId);
	Node p = head;
	while (p != NULL){
		if(p->data.Id == BookId){
			found = 1;
			break;
		}
		p=p->next;
	}
	if(found){
		int newId;
		printf("Nhap ma so sach moi: \n");
        scanf("%d", &newId);
        p->data.Id = newId;
	}
	else{
		printf("khong co ma so do. \n");
	}
	return head;
  
}

Node fixBookName(Node head){
	int BookId;
	int found = 0;
	printf("nhap ma so sach can nhan :\n");
	scanf("%d",&BookId);
	getchar();
	Node p = head;
	while (p != NULL){
		if(p->data.Id == BookId){
			found = 1;
			break;
		}
		p=p->next;
	}
	if(found){
	   char newName [100];
	   printf("Nhap ten sach moi: \n");
	   fgets(newName, sizeof(newName),stdin);
	   newName[strlen(newName)-1]='\0';
	   strcpy(p->data.bookName,newName);
	}else{
		printf("khong co ma so do. \n");
	}
	return head;
}

Node fixAuthor(Node head){
	int BookId;
	int found = 0;
	printf("nhap ma so sach can nhan :\n");
	scanf("%d",&BookId);
	getchar();
	Node p = head;
	while (p != NULL){
		if(p->data.Id == BookId){
			found = 1;
			break;
		}
		p=p->next;
	}
	if(found){
	   char newAuthor [100];
	   printf("Nhap ten tac gia moi: \n");
	   fgets(newAuthor, sizeof(newAuthor),stdin);
	   newAuthor[strlen(newAuthor)-1]='\0';
	   strcpy(p->data.Author,newAuthor);
	}else{
		printf("khong co ma so do. \n");
	}
	return head;
}
	
Node fixPublisher(Node head){
	int BookId;
	int found = 0;
	printf("nhap ma so sach can nhan :\n");
	scanf("%d",&BookId);
	getchar();
	Node p = head;
	while (p != NULL){
		if(p->data.Id == BookId){
			found = 1;
			break;
		}
		p=p->next;
	}
	if(found){
	   char newPublisher [100];
	   printf("Nhap ten nha xuat ban moi: \n");
	   fgets(newPublisher, sizeof(newPublisher),stdin);
	   newPublisher[strlen(newPublisher)-1]='\0';
	   strcpy(p->data.Publisher,newPublisher);
	}else{
		printf("khong co ma so do. \n");
	}
	return head;
}
Node fixPublishYear(Node head){
	int BookId;
	int found = 0;
	printf("nhap ma so sach can nhan :\n");
	scanf("%d",&BookId);
	Node p = head;
	while (p != NULL){
		if(p->data.Id == BookId){
			found = 1;
			break;
		}
		p=p->next;
	}
	if(found){
	   int newYear;
	   printf("Nhap nam moi: \n");
	   scanf("%d",&newYear);
	   p->data.publishYear = newYear;
	}else{
		printf("khong co ma so do. \n");
	}
	return head;
}

Node fixAmount(Node head){
	int BookId;
	int found = 0;
	printf("nhap ma so sach can nhan :\n");
	scanf("%d",&BookId);
	Node p = head;
	while (p != NULL){
		if(p->data.Id == BookId){
			found = 1;
			break;
		}
		p=p->next;
	}
	if(found){
	    int newAmount;
        printf("Nhap so luong moi : \n");
        scanf("%d", &newAmount);
        p->data.Amount = newAmount;
	}else{
		printf("khong co ma so do. \n");
	}
	return head;
	
}

Node fix_Book(Node head){
	int choice;
	while (TRUE){
		system("cls");
		displayall( head);
		printf("\n -*-*-*-*-*-*-*-*-*-*Sua thong tin sach-*-*-*-*-*-*-*-*-*-* \n");
	    printf("\n 1.Thay doi id. \n");	
	    printf("\n 2.Thay doi ten sach. \n");
	    printf("\n 3.Thay doi tac gia. \n");
	    printf("\n 4.Thay doi nha xuat ban. \n");
	    printf("\n 5.Thay doi nam xuat ban. \n");
	    printf("\n 6.Thay doi so luong sach. \n");
	    printf("\n 0.Thoat chuc nang. \n");
	    printf("\n =============================================================================== \n ");
        printf("Nhap lua chon : ");
        scanf("%d", &choice);
        switch (choice){
        	case 1:
        		head = fixId(head);
				break;
			case 2:
				head = fixBookName(head);
				break;
			case 3:
				head = fixAuthor(head);
				break;
			case 4:
				head = fixPublisher(head);
				break;
			case 5:
				head = fixPublishYear(head);
				break;
			case 6:
				head = fixAmount(head);
				break;
			case 0:
				printf("Thoat chuc nang. \n");
	        	getch();
	            return head;
	          default:
	        	printf("khong co chuc nang nay. xin vui long chon chuc nang khac.\n");
	        	printf("Nhap phim bat ki \n");
	        	getch();
	        	break;
		}
		getch();
	}
	return head;
}


Node writeData(Node head){
	printf("Nhap ten file : ");
	getchar();
	char fileName [50];
	fgets(fileName,sizeof(fileName),stdin);
	fileName[strlen(fileName)-1] = '\0';
	FILE*f = fopen("sach.txt", "w");
	if(f==NULL){
		printf("loi tao hoac mo file");
		exit (1);
	}
	for (Node p = head; p != NULL; p = p->next) 
    {
        fprintf(f, "%d,", p->data.Id);
        fprintf(f, "%s,", p->data.bookName);
        fprintf(f, "%s,", p->data.Author);
        fprintf(f, "%s,", p->data.Publisher);
        fprintf(f, "%d,", p->data.publishYear);
        fprintf(f, "%d,", p->data.used);
        fprintf(f, "%d\n", p->data.Amount);
    }
    fclose(f);
    printf("Da ghi danh sach vao file %s thanh cong.\n", fileName);
}






	


