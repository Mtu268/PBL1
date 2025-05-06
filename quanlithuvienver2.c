#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define TRUE 1
#define FALSE 0
#define INVALID_BOOK_ID -1

// Khai báo kiểu cấu trúc book
typedef struct Book
{
    int Id;

    char BookName[60], Author[60], Publisher[60];
    
    int PublishYear;

    int used;

    int BR;

    int Amount;
} Book;

typedef struct Book book;

// Khai báo kiểu cấu trúc Node
typedef struct BookNode
{
    book data;
    struct BookNode *next;
} BookNode;

typedef struct BookNode *Node;

Node initHead();
book handleLineData(char *line);
Node readData(Node head);
Node Createbooknode(book Book);
book createBook();
Node InsertFirst(Node head, book value);    
Node InsertLast(Node head, book value);
Node InsertAfter(Node head, int id);
Node Insert_Book(Node head);
Node delfirst(Node head); 
Node dellast(Node head); 
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
void swapstring(char *x, char *y);
void swapint(int *x, int *y);
void sortBookName(Node head);
void sortAuthor(Node head);
void sortPublisher(Node head);
void sortPublishYear(Node head);
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
int sl(Node head, int choose);
int sl_book(Node head);
Node writeData(Node head);

int main() 
{
    int option;
    Node head = initHead();
    while(TRUE) 
    {
        system("cls");
        printf("\n ***************QUAN LY SACH TRONG THU VIEN************  \n");
        printf("\n =========================MENU=========================  \n");
        printf("\n 1.Khoi tao danh sach. \n");
        printf("\n 2.Them mot cuon sach vao danh sach. \n");
        printf("\n 3.Xoa mot cuon sach khoi danh sach. \n");
        printf("\n 4.Tim kiem sach. \n");
        printf("\n 5.Xem danh sach. \n");
        printf("\n 6.Muon/tra sach. \n");
        printf("\n 7.Chinh sua noi dung cua sach. \n");
        printf("\n 8.Luu file. \n");
        printf("\n 9.Xem so luong sach \n");
        printf("\n 0.Thoat. \n");
        printf("\n ====================================================== \n");
        printf("Nhap chuc nang : ");
        scanf("%d", &option);
        switch(option) 
        {
            case 1 :
                head = readData(head);
                break;
            case 2 :
                head = Insert_Book(head);
                break;
            case 3 :
                head = del_Book(head);
                break;
            case 4 :
                find_Book(head);
                break;
            case 5 :
                display_Book(head);
                break;
            case 6 :
                head = borrow_giveback_Book(head);
                break;
            case 7 :
                head = fix_Book(head);
                break;
            case 8 :
                head = writeData(head);
                break;
            case 9 :
                sl_book(head);
                break;
            case 0 :
                printf(" Ban da thoat chuc nang nay. \n");
			    getch();
			    return 0;
            default :
                printf(" Khong co chuc nang nay \n");
			    printf(" Hay chon chuc nang khac trong menu \n");
			    printf(" Nhap phim bat ki \n");
			    getch();
			    break;
        }
    }    
    return 0;
}

//Hàm khởi tạo Node đầu tiên
Node initHead()
{
    Node head;
    head = NULL;
    return head;
}

// Hàm tách các thành phần của 1 dòng trong file
book handleLineData(char *line)
{
    book book;
    book.Id = INVALID_BOOK_ID; // Khởi tạo giá trị không hợp lệ. Về sau ta có thể kiểm tra.
    char *tmp;
    tmp = strtok(line, ",");
    if (tmp == NULL) {
        printf("Du lieu khong dung dinh dang: %s", line);
        exit(EXIT_FAILURE);
    }
    book.Id = atoi(tmp);
    int index = 0;
    for (;;index++) 
    {
        tmp = strtok(NULL, ",");
        if (tmp == NULL)
            break;
        if (index == 0)
        {
            strcpy(book.BookName, tmp);
        }
        else if (index == 1)
        {
            strcpy(book.Author, tmp);
        }
        else if (index == 2)
        {
            strcpy(book.Publisher, tmp);
        }
        else if (index == 3)
        {
            book.PublishYear = atoi(tmp);
        }
        else if (index == 4)
        {
            book.used = atoi(tmp);
        }
        else if (index == 5)
        {
            book.Amount = atoi(tmp);
        }
        else 
        {
            printf("Du lieu khong dung dinh dang: %s", line);
            exit(EXIT_FAILURE);
        }
    }
    book.BR = 0;
    return book;
}

// Hàm đọc dữ liệu từ tập tin
Node readData(Node head)
{
    char fileName[40];
    printf("Nhap ten file :");
    fflush(stdin);
    gets(fileName);
    FILE* file = fopen(fileName, "r");
    if(!file){
        printf("Co loi khi mo file : %s\n", fileName);
        exit(EXIT_FAILURE);
    }
    char line[500];
    while (fgets(line, sizeof(line), file)) {
        book book = handleLineData(line);
        if (book.Id != INVALID_BOOK_ID) {
            head = InsertLast(head, book);
        }
    }
    fclose(file);
    getch();
    return head;
}

// Hàm tạo mới 1 Node trong BookNode
Node Createbooknode(book Book)
{
    Node p;
    p = (Node)malloc(sizeof(struct BookNode));
    p->data = Book;
    p->next = NULL;
    return p;
}

//Nhập thông tin mỗi quyển sách
book createBook()
{
    book newBook;
    printf("Nhap ma so sach: ");
    scanf("%d", &newBook.Id);
    printf("Nhap ten sach: ");
    fflush(stdin);
    gets(newBook.BookName);
    printf("Nhap ten tac gia: ");
    fflush(stdin);
    gets(newBook.Author);
    printf("Nhap nha xuat ban: ");
    fflush(stdin);
    gets(newBook.Publisher);
    printf("Nhap nam xuat ban: ");
    scanf("%d", &newBook.PublishYear);
    printf("Nhap so lan sach da duoc muon: ");
    scanf("%d", &newBook.used);
    printf("Nhap so luong sach: ");
    scanf("%d", &newBook.Amount);
    newBook.BR = 0;
    return newBook;
}

// Thêm vào đầu
Node InsertFirst(Node head, book value) 
{
    Node temp = Createbooknode(value);
    if(head == NULL) 
    {
        head = temp;
    }
    else 
    {
        temp->next = head;
        head = temp;
    }
    return head;
}

// Thêm vào cuối 
Node InsertLast(Node head, book value) 
{
    Node temp,p;
    temp = Createbooknode(value);
    if(head == NULL) 
    {
        head = temp;
    }
    else 
    {
        p = head;
        while(p->next != NULL)
        {
            p = p->next;
        }
        p->next = temp;
    }
    return head;
}

// Thêm vào sau một cuốn sách 
Node InsertAfter(Node head, int id) 
{
    if(head == NULL) 
    {
        book value = createBook();
        head = InsertFirst(head,value);
    }
    else 
    {
        int found = 1;
        for(Node p = head; p->next != NULL; p = p->next)
        {
            if(p->data.Id == id) 
            {
                found = 0;
                book value = createBook();
                Node temp = Createbooknode(value);
                temp->next = p->next;
                p->next = temp;
                break;
            }
        }
        if(found) 
        {
            printf("Khong tim thay vi tri nay !!! ");
        }
    }
    return head;
}

Node Insert_Book(Node head) 
{
    int option,id;
    while(TRUE) 
    {
        system("cls");
        printf("\n --------------------Them sach-------------------- \n");
        printf("\n 1.Them cuon sach vao dau danh sach. \n");
        printf("\n 2.Them cuon sach vao sau mot cuon sach nao do. \n");
        printf("\n 3.Them cuon sach vao cuoi danh sach. \n");
        printf("\n 0.Thoat. \n");
        printf("\n ------------------------------------------------- \n");
        printf("Nhap lua chon : ");
        scanf("%d", &option);
        switch(option) 
        {
            case 1 :
                if(TRUE){
                book value = createBook();
                head = InsertFirst(head,value);
                break;
                }
            case 2 :
                if(TRUE){
                printf("Nhap vi tri sach can them : ");
                scanf("%d", &id);
                head = InsertAfter(head,id);
                break;
                }
            case 3 :
                if(TRUE){
                book value = createBook();
                head = InsertLast(head,value);
                break;
                }
            case 0 :
                printf(" Ban da thoat chuc nang nay. \n");
			    getch();
			    return head;
            default :
                printf(" Khong co chuc nang nay \n");
			    printf(" Hay chon chuc nang khac trong menu \n");
			    printf(" Nhap phim bat ki \n");
			    getch();
			    break;
        }
        getch();
    }
    return head;
}

//Xoá Node đầu tiên
Node delfirst(Node head) 
{
   if(head == NULL) 
   {
       printf("Khong co gi de xoa ! ");
   }
   else 
   {
       head = head->next;
   }
   return head;
}

//Xoá Node cuối cùng
Node dellast(Node head) 
{
    if(head == NULL || head->next == NULL) 
    {
        return delfirst(head);
    }
    Node p = head;
    while(p->next->next != NULL) 
    {
        p = p->next;
    }
    p->next = p->next->next;
    return head;
}

//Xoá Node theo Id 
Node delId(Node head) 
{
   int id; 
   int found = 1;
   printf("Nhap ma so sach can xoa: ");
   scanf("%d", &id);
    if(head == NULL || head->data.Id == id)
    {
        head = delfirst(head);
    }
    else 
    {
        for(Node p = head; p->next != NULL; p = p->next)
        {
            if(p->next->data.Id == id) 
            {
                found = 0;
                p->next = p->next->next;
                break;
            }
        }
        if(found) 
        {
            printf("Khong tim thay vi tri nay !!! ");
        }
    }
    return head;
}

//Xoá Node sau một Id nào đó
Node delAfter(Node head) 
{
   int id; 
   printf("Nhap ma so sach truoc sach can xoa: ");
   scanf("%d", &id);
    if(head == NULL)
    {
        head = delfirst(head);
    }
    else 
    {
        int found = 1;
        for(Node p = head; p->next != NULL; p = p->next)
        {
            if(p->data.Id == id) 
            {
                found = 0;
                p->next = p->next->next;
            }
        }
        if(found) 
        {
            printf("Khong tim thay vi tri nay !!! ");
        }
    }
    return head;
}

//Xoá Node theo tên tác sach 
Node delBookName(Node head) 
{
   char bookname[60]; 
   printf("Nhap ten sach can xoa: ");
   fflush(stdin);
   gets(bookname);
    if(head == NULL || strcmp(strupr(head->data.BookName), strupr(bookname)) == 0)
    {
        head = delfirst(head);
    }
    else 
    {
        int found = 1;
        for(Node p = head; p->next != NULL; p = p->next)
        {
            if(strcmp(strupr(p->next->data.BookName), strupr(bookname)) == 0)
            {
                p->next = p->next->next;
                found = 0;
                break;
            }
        }
        if(found)
        {
            printf("Khong co ten sach nay trong thu vien !!! ");
        }
    }
    return head;
}

//Xoá Node theo tên tác giả
Node delAuthor(Node head)
{
    char author[60];
    printf("Nhap ten tac gia can xoa: ");
    fflush(stdin);
    gets(author);
    if (head == NULL)
    {
        head = delfirst(head);
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

Node del_Book(Node head) 
{
    int option,position;
    while(TRUE) 
    {
        system("cls");
        printf("\n --------------------Xoa sach-------------------- \n");
        printf("\n 1.Xoa cuon sach  theo ma so. \n");
        printf("\n 2.Xoa cuon sach  theo ten sach. \n");
        printf("\n 3.Xoa cuon sach  theo ten tac gia. \n");
        printf("\n 4.Xoa cuon sach  o dau danh sach. \n");
        printf("\n 5.Xoa cuon sach  o sau cuon sach co ma so nao do. \n");
        printf("\n 6.Xoa cuon sach  o cuoi danh sach. \n");
        printf("\n 0.Thoat. \n");
        printf("\n ------------------------------------------------- \n");
        printf("Nhap lua chon : ");
        scanf("%d", &option);
        switch(option) 
        {
            case 1 :
                head = delId(head);
                break;
            case 2 :
                head = delBookName(head);
                break;
            case 3 :
                head = delAuthor(head);
                break;
            case 4 :
                head = delfirst(head);
                break;
            case 5 :
                head = delAfter(head);
                break;
            case 6 :
                head = dellast(head);
                break;
            case 0 :
                printf(" Ban da thoat chuc nang nay. \n");
			    getch();
			    return head;
            default :
                printf(" Khong co chuc nang nay \n");
			    printf(" Hay chon chuc nang khac trong menu \n");
			    printf(" Nhap phim bat ki \n");
			    getch();
			    break;
        }
        getch();

    }
    return head;
}

//Tìm kiếm theo tên sách
void findBookName(Node head) 
{
    Node p;
    char bookname[60];
    printf("Nhap ten quyen sach can tim: \n");
    fflush(stdin);
    gets(bookname);
    printf("Danh sach hien tai:\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%10s%30s%25s%20s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So lan muon", "So luong");
    for(p = head; p != NULL; p = p->next)
    {
        if(strcmp(strupr(p->data.BookName), strupr(bookname)) == 0)
        {
            display(p);
        }
    }
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
}

//Tìm kiếm theo tên tác giả
void findAuthor(Node head) 
{
    Node p;
    char author[60];
    printf("Nhap ten tac gia can tim: \n");
    fflush(stdin);
    gets(author);
    printf("Danh sach hien tai:\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%10s%30s%25s%20s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So lan muon", "So luong");
    for(p = head; p != NULL; p = p->next)
    {
        if(strcmp(strupr(p->data.Author), strupr(author)) == 0)
        {
            display(p);
        }
    }
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
}

//Tìm kiếm theo tên nhà xuất bản
void findPublisher(Node head) 
{
    Node p;
    char publisher[60];
    printf("Nhap ten tac gia can tim: \n");
    fflush(stdin);
    gets(publisher);
    printf("Danh sach hien tai:\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%10s%30s%25s%20s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So lan muon", "So luong");
    for(p = head; p != NULL; p = p->next)
    {
        if(strcmp(strupr(p->data.Publisher), strupr(publisher)) == 0)
        {
            display(p);
        }
    }
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
}

int find_Book(Node head) 
{
    int option,position;
    while(TRUE) 
    {
        system("cls");
        printf("\n ----------Tim sach---------- \n");
        printf("\n 1.Tim theo ten sach. \n");
        printf("\n 2.Tim theo ten tac gia. \n");
        printf("\n 3.Tim theo ten nha xuat ban. \n");
        printf("\n 0.Thoat. \n");
        printf("\n ---------------------------- \n");
        printf("Nhap lua chon : ");
        scanf("%d", &option);
        switch(option) 
        {
            case 1 :
                findBookName(head);
                break;
            case 2 :
                findAuthor(head);
                break;
            case 3 :
                findPublisher(head);
                break;
            case 0 :
                printf(" Ban da thoat chuc nang nay. \n");
			    getch();
			    return 0;
            default :
                printf(" Khong co chuc nang nay \n");
			    printf(" Hay chon chuc nang khac trong menu \n");
			    printf(" Nhap phim bat ki \n");
			    getch();
			    break;
        }
        getch();
    }
}

//Liệt kê một cuốn sách
void display(Node p) 
{
    printf("%10d%30s%25s%20s%16d%20d%15d\n", p->data.Id, p->data.BookName, p->data.Author, p->data.Publisher, p->data.PublishYear, p->data.used, p->data.Amount);
}

//Liệt kê toàn bộ sách
void displayall(Node head)
{
    Node p;
    printf("Danh sach hien tai:\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%10s%30s%25s%20s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So lan muon", "So luong");
    for(p = head; p != NULL; p = p->next)
    {
        display(p);
    }
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
}

//Liệt kê sách chưa cho mượn
void displayAvailable(Node head) 
{
    Node p;
    printf("Danh sach hien tai:\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%10s%30s%25s%20s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So lan muon", "So luong");
    for(p = head; p != NULL; p = p->next)
    {
        if(p->data.Amount > 0)
        {
           display(p);
        }
    }
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
}

//Liệt kê sách đang cho mượn 
void displayNotAvailable(Node head) 
{
    Node p;
    printf("Danh sach hien tai:\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%10s%30s%25s%20s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So lan muon", "So luong");
    for(p = head; p != NULL; p = p->next)
    {
        if(p->data.Amount == 0)
        {
            display(p);
        }
    }
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
}

//Hàm hoán đổi chuỗi
void swapstring(char *x, char *y)
{
    char temp[60];
    strcpy(temp,x);
    strcpy(x,y);
    strcpy(y,temp);
}

//Hàm hoán đổi số
void swapint(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

//Xem danh sách theo thứ tự: Theo vần alphabet của tên sách
void sortBookName(Node head) 
{
    for(Node p = head; p != NULL; p = p->next) 
    {
        Node t = p;
        for(Node q = p->next; q != NULL; q = q->next)
        {
            if(strcmp(t->data.BookName,q->data.BookName) > 0)
            {
                t = q;
            }
        }
        swapint(&t->data.Id,&p->data.Id);
        swapstring(t->data.BookName,p->data.BookName);
        swapstring(t->data.Author,p->data.Author);
        swapstring(t->data.Publisher,p->data.Publisher);
        swapint(&t->data.PublishYear,&p->data.PublishYear);
        swapint(&t->data.used,&p->data.used);
        swapint(&t->data.BR,&p->data.BR);
        swapint(&t->data.Amount,&p->data.Amount);
    }
    displayall(head);
}

//Xem danh sách theo thứ tự: Theo vần alphabet của tên tác giả
void sortAuthor(Node head) 
{
    for(Node p = head; p != NULL; p = p->next) 
    {
        Node t = p;
        for(Node q = p->next; q != NULL; q = q->next)
        {
            if(strcmp(t->data.Author,q->data.Author) > 0)
            {
                t = q;
            }
        }
        swapint(&t->data.Id,&p->data.Id);
        swapstring(t->data.BookName,p->data.BookName);
        swapstring(t->data.Author,p->data.Author);
        swapstring(t->data.Publisher,p->data.Publisher);
        swapint(&t->data.PublishYear,&p->data.PublishYear);
        swapint(&t->data.used,&p->data.used);
        swapint(&t->data.BR,&p->data.BR);
        swapint(&t->data.Amount,&p->data.Amount);
    }
    displayall(head);
}

//Xem danh sách theo thứ tự: Theo vần alphabet của tên nhà xuất bản
void sortPublisher(Node head) 
{
    for(Node p = head; p != NULL; p = p->next) 
    {
        Node t = p;
        for(Node q = p->next; q != NULL; q = q->next)
        {
            if(strcmp(t->data.Publisher,q->data.Publisher) > 0)
            {
                t = q;
            }
        }
        swapint(&t->data.Id,&p->data.Id);
        swapstring(t->data.BookName,p->data.BookName);
        swapstring(t->data.Author,p->data.Author);
        swapstring(t->data.Publisher,p->data.Publisher);
        swapint(&t->data.PublishYear,&p->data.PublishYear);
        swapint(&t->data.used,&p->data.used);
        swapint(&t->data.BR,&p->data.BR);
        swapint(&t->data.Amount,&p->data.Amount);
    }
    displayall(head);
}

//Xem danh sách theo thứ tự: Sách được xuất bản mới nhất (theo năm)
void sortPublishYear(Node head) 
{
    for(Node p = head; p != NULL; p = p->next) 
    {
        Node t = p;
        for(Node q = p->next; q != NULL; q = q->next)
        {
            if(t->data.PublishYear < q->data.PublishYear)
            {
                t = q;
            }
        }
        swapint(&t->data.Id,&p->data.Id);
        swapstring(t->data.BookName,p->data.BookName);
        swapstring(t->data.Author,p->data.Author);
        swapstring(t->data.Publisher,p->data.Publisher);
        swapint(&t->data.PublishYear,&p->data.PublishYear);
        swapint(&t->data.used,&p->data.used);
        swapint(&t->data.BR,&p->data.BR);
        swapint(&t->data.Amount,&p->data.Amount);
    }
    displayall(head);
}

int display_Book(Node head) 
{
    int option,position;
    char op;
    while(TRUE) 
    {
        system("cls");
        printf("\n ----------Xem danh sach---------- \n");
        printf("\n 1.Xem toan bo danh muc sach. \n");
        printf("\n 2.Xem sach da cho muon het. \n");
        printf("\n 3.Xem sach van con . \n");
        printf("\n 4.Xem theo thu tu alphabet cua ten sach. \n");
        printf("\n 5.Xem theo thu tu alphabet cua ten tac gia. \n");
        printf("\n 6.Xem theo thu tu alphabet cua ten nha xuat ban. \n");
        printf("\n 7.Xem theo thu tu sach xuat ban moi nhat. \n");
        printf("\n 0.Thoat. \n");
        printf("\n ---------------------------- \n");
        printf("Nhap lua chon : ");
        scanf("%d", &option);
        switch(option) 
        {
            case 1 :
                displayall(head);
                break;
            case 2 :
                displayNotAvailable(head);
                break;
            case 3 :
                displayAvailable(head);
                break;
            case 4 :
                sortBookName(head);
                break;
            case 5 :
                sortAuthor(head);
                break;
            case 6 :
                sortPublisher(head);
                break;
            case 7 :
                sortPublishYear(head);
                break;
            case 0 :
                printf(" Ban da thoat chuc nang nay. \n");
			    getch();
			    return 0;
            default :
                printf(" Khong co chuc nang nay \n");
			    printf(" Hay chon chuc nang khac trong menu \n");
			    printf(" Nhap phim bat ki \n");
			    getch();
                system("cls");
			    break;
        }
        getch();
    }
}

//Mượn sách
Node borrow(Node head) 
{
    displayAvailable(head);
    int ms,found = 0;
    printf("Nap ma so sach can muon: \n");
    scanf("%d", &ms);
    for(Node p = head; p != NULL; p = p->next)
    {
        if(p->data.Id == ms && p->data.Amount > 0) 
        {
            p->data.Amount -= 1;
            p->data.used += 1;
            found = 1;
            p->data.BR += 1;
            break;
        }
    }
    if(found == 0) printf("Khong tim thay ma so sach nay trong thu vien sach chua cho muon!!! \n");
    return head;
}

//Trả sách
Node giveback(Node head) 
{
    int ms,found = 0;
    printf("Nap ma so sach can tra: \n");
    scanf("%d", &ms);
    for(Node p = head; p != NULL; p = p->next)
    {
        if(p->data.Id == ms && p->data.BR > 0 ) 
        {
            p->data.Amount += 1;
            found = 1;
            p->data.BR -= 1;
            break;
        }
    }
    if(found == 0) printf("Khong tim thay ma so sach nay trong thu vien sach dang cho muon!!! \n");
    return head;
}

Node borrow_giveback_Book(Node head) 
{
    int option,position;
    while(TRUE) 
    {
        system("cls");
        printf("\n ----------Muon/tra sach---------- \n");
        printf("\n 1.Muon sach. \n");
        printf("\n 2.Tra sach. \n");
        printf("\n 0.Thoat. \n");
        printf("\n ---------------------------- \n");
        printf("Nhap lua chon : ");
        scanf("%d", &option);
        switch(option) 
        {
            case 1 :
                head = borrow(head);
                break;
            case 2 :
                head = giveback(head);
                break;
            case 0 :
                printf(" Ban da thoat chuc nang nay. \n");
			    getch();
			    return head;
            default :
                printf(" Khong co chuc nang nay \n");
			    printf(" Hay chon chuc nang khac trong menu \n");
			    printf(" Nhap phim bat ki \n");
			    getch();
			    break;
        }
        getch();
    }
    return head;
}

//Sửa mã số sách
Node fixId(Node head) 
{
    int ms,found = 0;
    Node p;
    printf("Nhap ma so sach can sua: \n");
    scanf("%d", &ms);
    for(p = head; p != NULL; p = p->next) 
    {
        if(p->data.Id == ms)
        {
            found = 1;
            break;
        }
    }
    if(found) 
    {
        int newId;
        printf("Nhap ma so sach moi: \n");
        scanf("%d", &newId);
        p->data.Id = newId;
    }
    else printf("Khong tim thay ma so sach !!! \n");
    return head;
}

//Sửa tên sách
Node fixBookName(Node head) 
{
    int ms,found = 0;
    Node p;
    printf("Nhap ma so sach can sua: \n");
    scanf("%d", &ms);
    for(p = head; p != NULL; p = p->next) 
    {
        if(p->data.Id == ms)
        {
            found = 1;
            break;
        }
    }
    if(found) 
    {
        char newBookName[60];
        printf("Nhap ten sach moi: \n");
        fflush(stdin);
        gets(newBookName);
        strcpy(p->data.BookName,newBookName);
    }
    else printf("Khong tim thay ma so sach !!! \n");
    return head;
}

//Sửa tên tác giả
Node fixAuthor(Node head) 
{
    int ms,found = 0;
    Node p;
    printf("Nhap ma so sach can sua: \n");
    scanf("%d", &ms);
    for(p = head; p != NULL; p = p->next) 
    {
        if(p->data.Id == ms)
        {
            found = 1;
            break;
        }
    }
    if(found) 
    {
        char newAuthor[60];
        printf("Nhap ten tac gia moi: \n");
        fflush(stdin);
        gets(newAuthor);
        strcpy(p->data.Author,newAuthor);
    }
    else printf("Khong tim thay ma so sach !!! \n");
    return head;
}

//Sửa nhà xuất bản
Node fixPublisher(Node head) 
{
    int ms,found = 0;
    Node p;
    printf("Nhap ma so sach can sua: \n");
    scanf("%d", &ms);
    for(p = head; p != NULL; p = p->next) 
    {
        if(p->data.Id == ms)
        {
            found = 1;
            break;
        }
    }
    if(found) 
    {
        char newPublisher[60];
        printf("Nhap nha xuat ban moi: \n");
        fflush(stdin);
        gets(newPublisher);
        strcpy(p->data.Publisher,newPublisher);
    }
    else printf("Khong tim thay ma so sach !!! \n");
    return head;
}

//Sửa năm xuất bản
Node fixPublishYear(Node head) 
{
    int ms,found = 0;
    Node p;
    printf("Nhap ma so sach can sua: \n");
    scanf("%d", &ms);
    for(p = head; p != NULL; p = p->next) 
    {
        if(p->data.Id == ms)
        {
            found = 1;
            break;
        }
    }
    if(found) 
    {
        int newPublishYear;
        printf("Nhap nam xuat ban moi: \n");
        scanf("%d", &newPublishYear);
        p->data.PublishYear = newPublishYear;
    }
    else printf("Khong tim thay ma so sach !!! \n");
    return head;
}

//Sửa số lần mượn sách
Node fixUsed(Node head) 
{
    int ms,found = 0;
    Node p;
    printf("Nhap ma so sach can sua: \n");
    scanf("%d", &ms);
    for(p = head; p != NULL; p = p->next) 
    {
        if(p->data.Id == ms)
        {
            found = 1;
            break;
        }
    }
    if(found) 
    {
        int newUsed;
        printf("Nhap so lan muon moi: \n");
        scanf("%d", &newUsed);
        p->data.used = newUsed;
    }
    else printf("Khong tim thay ma so sach !!! \n");
    return head;
}

//Sửa số lượng sách
Node fixAmount(Node head) 
{
    int ms,found = 0;
    Node p;
    printf("Nhap ma so sach can sua: \n");
    scanf("%d", &ms);
    for(p = head; p != NULL; p = p->next) 
    {
        if(p->data.Id == ms)
        {
            found = 1;
            break;
        }
    }
    if(found) 
    {
        int newAmount;
        printf("Nhap so luong moi : \n");
        scanf("%d", &newAmount);
        p->data.Amount = newAmount;
    }
    else printf("Khong tim thay ma so sach !!! \n");
    return head;
}

Node fix_Book(Node head) 
{
    
    int option,position;
    while(TRUE) 
    {
        system("cls");
        displayall(head);
        printf("\n ----------Chinh sua noi dung sach---------- \n");
        printf("\n 1.Chinh sua ma so sach. \n");
        printf("\n 2.Chinh sua ten sach. \n");
        printf("\n 3.Chinh sua ten tac gia. \n");
        printf("\n 4.Chinh sua ten nha xuat ban. \n");
        printf("\n 5.Chinh sua nam xuat ban. \n");
        printf("\n 6.Chinh sua so lan muon sach. \n");
        printf("\n 7.Chinh sua so luong sach. \n");
        printf("\n 0.Thoat. \n");
        printf("\n ------------------------------------------- \n");
        printf("Nhap lua chon : ");
        scanf("%d", &option);
        switch(option) 
        {
            case 1 :
                head = fixId(head);
                break;
            case 2 :
                head = fixBookName(head);
                break;
            case 3 :
                head = fixAuthor(head);
                break;
            case 4 :
                head = fixPublisher(head);
                break;
            case 5 :
                head = fixPublishYear(head);
                break;
            case 6 :
                head = fixUsed(head);
                break;
            case 7 :
                head = fixAmount(head);
                break;
            case 0 :
                printf(" Ban da thoat chuc nang nay. \n");
			    getch();
			    return head;
            default :
                printf(" Khong co chuc nang nay \n");
			    printf(" Hay chon chuc nang khac trong menu \n");
			    printf(" Nhap phim bat ki \n");
			    getch();
			    break;
        }
        getch();
    }
    return head;
}

//Xem số lượng sách
int sl(Node head, int choose) 
{
    int total = 0, available = 0, BR = 0;
    for(Node p = head; p != NULL; p = p->next)
    {
        total += 1;
        available += p->data.Amount;
        BR += p->data.BR;
    }
    if(choose == 1) return total;
    if(choose == 2) return available;
    if(choose == 3) return BR;
    if(choose == 4) return (BR + available);
}

int sl_book(Node head) 
{
    int option,position;
    while(TRUE) 
    {
        system("cls");
        printf("\n ----------Xem so luong sach---------- \n");
        printf("\n 1.Xem tong so loai sach. \n");
        printf("\n 2.Xem so luong sach chua cho muon. \n");
        printf("\n 3.Xem so luong sach dang cho muon. \n");
        printf("\n 4.Xem tong so luong sach. \n");
        printf("\n 0.Thoat. \n");
        printf("\n ------------------------------------------- \n");
        printf("Nhap lua chon : ");
        scanf("%d", &option);
        switch(option) 
        {
            case 1 :
                printf("Tong so luong sach la : %d loai \n", sl(head,1));
                break;
            case 2 :
                printf("So luong sach chua cho muon la : %d cuon \n", sl(head,2));
                break;
            case 3 :
                printf("So luong sach dang cho muon la : %d cuon \n", sl(head,3));
                break;
            case 4 :
                printf("Tong so luong la : %d cuon \n", sl(head,4));
                break;
            case 0 :
                printf(" Ban da thoat chuc nang nay. \n");
			    getch();
			    return 0;
            default :
                printf(" Khong co chuc nang nay \n");
			    printf(" Hay chon chuc nang khac trong menu \n");
			    printf(" Nhap phim bat ki \n");
			    getch();
			    break;
        }
        getch();
    }
}

//Ghi file
Node writeData(Node head)
{
    char fileName[40];
    fflush(stdin);
    gets(fileName);
    FILE* file = fopen(fileName, "w");
    for(Node p = head; p != NULL; p = p->next) 
    {
        fprintf(file, "%d", p->data.Id);
        fputs(",", file);
        fputs(p->data.BookName, file);
        fputs(",", file);
        fputs(p->data.Author, file);
        fputs(",", file);
        fputs(p->data.Publisher, file);
        fputs(",", file);
        fprintf(file, "%d", p->data.PublishYear);
        fputs(",", file);
        fprintf(file, "%d", p->data.used);
        fputs(",", file);
        fprintf(file, "%d",p->data.Amount);
        fputs("\n", file);
    }
    fclose(file);
}