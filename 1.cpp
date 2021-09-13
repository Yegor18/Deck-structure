#include <iostream>
#include <cstdlib>
//#include <ctime>
#include <time.h>
#include <windows.h>
#include <fstream>
using namespace std;
unsigned long long int nop = 0; 
class element{
	public:
		int value;
		element *next;
		element *prev;
};

class Deque{
	public:
		int size;
		element* head;
		element* tail;

	Deque(){
		size=0;
		head=0;
		tail=0;
		nop++;
	}

void AddL(int el)//8
{
	nop++;//ïðîâåðêà óñëîâèÿ
    if (size==0)//1
     {
         element *a=new element;//1
         a->next=0;//1
         a->prev=0;//1
         a->value=el;//1
         head=a;//1
         size++;//1
		nop+=6;
     }
     else{
        element *a = new element;//1
        a->next = head;//1
        a->prev =  0;//1
        a->value=el;//1
        head->prev=a;//1
        head=a;//1
        size++;//1
        nop+=7;
     }
};
	void AddR(int el)//6
	{
		nop++;
		if (head==0)//1
		{
		head = new element;//1
		tail=head;//1
		head->value=el;//1
		head->next=0;//1
		nop+=4;
	}
	else{
		tail->next=new element;//1
		tail->next->value=el;//1
		tail->next->next=0;//1
		tail=tail->next;//1
		nop+=4;
	}
	size++;
	nop++;
	};
	void DeleteR()//1+1+1+2(n-2)+2+1=2n+2
	{
		nop++;
	element *f = head;//1
	nop++;
    if (f == tail)//1
    {
               delete f;
                head = tail = NULL;//2
                nop+=3;
    }
    else
    {
    	nop++;
        while (f->next != tail)//1
		{
		f = f->next;//1
		nop+=2;
		}
        delete tail;
        tail = f;
        tail->next = NULL;
        nop+=2;
    }
size--;
nop++;
	};

	void DeleteL()//7
	{
		nop++;
		if (getQueueSize()==0)//1
		return;
	else
	{nop++;
	if(head==tail)//1
		{
			head=0;//1
			nop++;
		}
	else{
		element *f;//1
		f=head;//1
		head=f->next;//1
		delete f;
		nop+=3;
	}
	}
	size--;
	nop++;
	};

	int getQueueSize()
	{
		return size;
	};

	bool isEmpty()//1
	{
		nop++;
		if (getQueueSize()==0)//1
		return 1;

	return 0;
	};




	int Value()//2
	{
		element* f3;//1
	f3 = head;//1
	nop+=2;
	return f3->value;
	};

	int ValueR()//2
	{
		element* f3;
	f3 = tail;
	nop+=2;
	return f3->value;
	};




};

void Prohod(Deque &q)//17
{
	int temp;//1
	temp = q.Value();//1+2
	nop+=2;
	q.DeleteL();//7
	q.AddR(temp);//6
	temp=0;//1
	nop++;
}

void Show(Deque &q){
	cout << "Âàø ìàññèâ - " << endl;
	cout << endl;
	for (int i=0; i<q.getQueueSize(); i++){
		cout << q.Value() << " ";
		Prohod(q);
	}
	cout << endl;
	cout << endl;
}


void set(Deque &q, int n, int ne)//20n-2
{
	
	for (int i=0; i<q.getQueueSize(); i++)//(n-1)*(3+17)+(3+7+6)
	{
		nop+=3;
		if (i==n)
		{
			q.DeleteL();//7
			q.AddR(ne);//6
		}
		else{
			Prohod(q);//17
		}
	}
	nop+=2;
}

int get(Deque &q, int n)//20n-20+19+1+2=20n+2
{

	int res=0;//1
	nop++;
	for (int i=0; i<q.getQueueSize(); i++)//(n-1)*(3+17)+(3+3+7+6)
	{
		nop+=3;
		if (i==n)//1
		{
			nop++;
			res=q.Value();//1+2
			q.DeleteL();//7
			q.AddR(res);//6
		}
		else{
			Prohod(q);//17
		}
	}
	nop+=2;
	return res;
}


void SortirovkaVstavkoy(Deque &q, int n){
	int temp, // âðåìåííàÿ ïåðåìåííàÿ äëÿ õðàíåíèÿ çíà÷åíèÿ ýëåìåíòà ñîðòèðóåìîãî ìàññèâà
        item; // èíäåêñ ïðåäûäóùåãî ýëåìåíòà
        nop+=2;
    for (int i= 0; i < n; i++)
    {
        temp = get(q , i); // èíèöèàëèçèðóåì âðåìåííóþ ïåðåìåííóþ òåêóùèì çíà÷åíèåì ýëåìåíòà ìàññèâà
        //1
        item = i-1; // çàïîìèíàåì èíäåêñ ïðåäûäóùåãî ýëåìåíòà ìàññèâà
        //2
        nop+=3;
        nop+=2;
        while(item >= 0 && get( q , item ) > temp) //2
		//  ïîêà èíäåêñ íå ðàâåí 0 è ïðåäûäóùèé ýëåìåíò ìàññèâà áîëüøå òåêóùåãî
        {
            set(q , item+1 , get( q , item )); //1 
			// ïåðåñòàíîâêà ýëåìåíòîâ ìàññèâà
            item--;//1
            nop+=4;
        }
            set(q , item+1 , temp);
            nop++;
    }
}



void RandomnoeZapolnenie(Deque &q, int n){
	for (int i=0; i<n; i++)
		q.AddR(-100+rand()%200);
}

void UdalenieVsego(Deque &q){
	int n=q.getQueueSize();
	for (int i=0; i<n; i++)
		q.DeleteL();
}
/**/
void menu(){
	cout << "0 - çàïîëíèòü ñëó÷àéíûìè ýëåìåíòàìè" << endl;
	cout << "1 - äîáàâèòü ýëåìåíò ñëåâà" << endl;
	cout << "2 - äîáàâèòü ýëåìåíò ñïðàâà" << endl;
	cout << "3 - óäàëèòü ýëåìåíò ñëåâà" << endl;
	cout << "4 - óäàëèòü ýëåìåíò ñïðàâà" << endl;
	cout << "5 - âûâåñòè ïåðâûé ýëåìåíò íà óäàëåíèå ñëåâà" << endl;
	cout << "6 - âûâåñòè ïåðâûé ýëåìåíò íà óäàëåíèå ñïðàâà" << endl;
	cout << "7 - ñîðòèðîâêà" << endl;
	cout << "8 - î÷èñòèòü âñå" << endl;
	cout << "9 - âûõîä" << endl;
};


int main(){
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	int h=0;
	Deque q;

	while (h!=9){
		menu();

		do{
		cin >> h;
		if (h<-1 or h>9)
			cout << "îøèáêà" << endl;
		}
		while (h<0 and h>9);

		switch (h){
			case 0:
				int nu;
				cout << "�'êîëüêî ýëåìåíòîâ ââåñòè?" << endl;
				cin >> nu;
				if (q.isEmpty()==0){
					cout << "Î÷åðåäü óæå ÷åì-òî çàïîëíåíà" << endl;
					system("pause");
				}
				else
					RandomnoeZapolnenie(q, nu);
				system("CLS");
				Show(q);
				break;
			case 1:
				int el;
				cout << "Ââåäèòå ýëåìåíò" << endl;
				cin >> el;
				q.AddL(el);
				system("CLS");
				Show(q);
				break;
            case 2:
				int el1;
				cout << "Ââåäèòå ýëåìåíò" << endl;
				cin >> el1;
				q.AddR(el1);
				system("CLS");
				Show(q);
				break;
			case 3:
				q.DeleteL();
				system("CLS");
				Show(q);
				break;
            case 4:
				q.DeleteR();
				system("CLS");
				Show(q);
				break;
			case 5:
				cout << endl;
				cout << "Ïåðâûé ýëåìåíò íà óäàëåíèå - " <<q.Value();
				cout << endl;
				system("pause");
				system("CLS");
				Show(q);
				break;
            case 6:
				cout << endl;
				cout << "Ïåðâûé ýëåìåíò íà óäàëåíèå - " <<q.ValueR();
				cout << endl;
				system("pause");
				system("CLS");
				Show(q);
				break;
			case 7:
				SortirovkaVstavkoy(q, q.getQueueSize());
				system("CLS");
				Show(q);
				break;
			case 8:
				UdalenieVsego(q);
				system("CLS");
				Show(q);
				break;
		}
	}


	return 1;
}

	/*int main()
	{
		srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	int h=0;
	Deque q;
		ofstream fl("andr.txt");
	for (int i=1;i<2001;i++)
	{
	//fl<<(rand());
	//fl<<-i;
	fl<<i;
	//fl<<1;
	fl<<" ";
	}
	fl.close();
	int i, N,b;
	for (N=200;N<2001;N+=200)
	{
	ifstream f("andr.txt");
	for (i=1;i<N;i++)
	{
	if(f >> b)
			{//cout << b << std::endl;	
			q.AddR(b);
			}
	}
	int t1,t2;
	
	nop=0;
	t1=GetTickCount();
	SortirovkaVstavkoy(q, q.getQueueSize());
				//cout<<endl<<nop;
	t2=GetTickCount();
	cout<<t1<<endl<<t2<<endl<<t2-t1<<endl;
	cout<<N/200<<") NOP "<<nop<<endl;
	UdalenieVsego(q);
	f.close();
	}
	}
*/
