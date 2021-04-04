#include <iostream>

using namespace std;

class Heap
{
private:
	int* kopiec; //tablica dynamiczna przechowujaca elementy kopca
	int capacity; //maksymalny rozmiar tablicy (kopca)
	int heap_size; //liczba elementow w tablicy, czyli liczba elementow kopca
public:
	Heap(int c); //tworzy pusty kopiec o pojemności c
	Heap();	//konstruktor do testów kopca - należy utworzyć kopiec nast. zawartością: 12,9,10,7,9,5,9,2,1,3
	bool empty();  //zwraca true, jesli kopiec jest pusty, false w przeciwnym razie
	bool full(); //zwraca true, jesli kopiec jest pelny, false w przeciwnym razie
	int left(int i); //zwraca pozycję lewego syna
	int right(int i); //zwraca pozycję prawego syna
	int parent(int i);	//zwraca pozycję ojca
	int getSize();	//zwraca rozmiar kopca
	void setHeapSize(int s); //ustawia rozmiar kopca
	int get(int i);	//zwraca wartość z pozycji i
	void set(int i, int x);	//ustawia wartość x na pozycji i
	void up(int i);	//przywraca własność kopca metodą wynurzania
	void down(int i); //przywraca własność kopca metodą zatapiania
	friend ostream& operator<<(ostream& out, Heap& h); //wyswietla kopiec na ekranie
};

/* należy utworzyć kopiec testowy
testowanie metod up() i down() - dla każdej:
modyfikacja wartość na wybranej pozycji kopca tak aby własność kopca nie była spełniona,
wywołanie metody dla zmienionej pozycji
wyświetlenie kopca
*/

Heap::Heap(int c)
{
	kopiec = new int[c];
	capacity = c;
	heap_size = 0;
}

Heap::Heap()
{
	capacity = 20;
	kopiec = new int[capacity] {12, 9, 10, 7, 9, 5, 9, 2, 1, 3};
	heap_size = 10;
}

bool Heap::empty()
{
	if (heap_size == 0)
		return true;
	return false;
}

bool Heap::full()
{
	if (heap_size == capacity)
		return true;
	return false;
}

int Heap::left(int i)
{
	if (!empty())
		return 2 * i + 1;
	return NULL;

	/**if (i >= 0)
		return 2 * i + 1;
	return -1;**/
}

int Heap::right(int i)
{
	if (!empty())
		return 2 * i + 2;
	return NULL;

	/**if (i >= 0)
		return 2 * i + 2;
	return -1;**/
}

int Heap::parent(int i)
{
	//jesli i jest korzeniem, to nie ma ojca
	if (((i - 1) / 2) >= 0 && i < heap_size)
		return int((i - 1) / 2);
	return NULL;
}

int Heap::getSize()
{
	return heap_size;
}

void Heap::setHeapSize(int s)
{
	heap_size = s;
}

int Heap::get(int i)
{
	if (i >= 0 && i < heap_size)
		return kopiec[i];
	return NULL;
}

void Heap::set(int i, int x)
{
	kopiec[i] = x;
}

void Heap::up(int i) //i to pozycja, od której zaczynamy wynurzanie
{
	int wartosc_na_pozycji_i;
	int pozycja_ojca_i;
	int wartosc_ojca_i;

	wartosc_na_pozycji_i = get(i);
	pozycja_ojca_i = parent(i);
	wartosc_ojca_i = get(pozycja_ojca_i);

	if (i > 0 && wartosc_na_pozycji_i > wartosc_ojca_i)
	{
		//pierwsza metoda rowniez dziala poprawnie
		//set(i, wartosc_ojca_i);
		//set(pozycja_ojca_i, wartosc_na_pozycji_i);
		swap(kopiec[pozycja_ojca_i], kopiec[i]);
		up(pozycja_ojca_i); //rekurencja
	}
}

void Heap::down(int i) //i to pozycja, od której rozpoczynamy zatapianie
{
	int pozycja_lewego_syna, pozycja_prawego_syna, temp;
	pozycja_lewego_syna = left(i);
	pozycja_prawego_syna = right(i);
	temp = i;

	if (get(pozycja_lewego_syna) > get(i) && pozycja_lewego_syna < heap_size)
		temp = pozycja_lewego_syna;
	if (get(pozycja_prawego_syna) > get(temp) && pozycja_prawego_syna < heap_size)
		temp = pozycja_prawego_syna;

	if (temp != i)
	{
		//pierwsza metoda dziala zle -> lepiej robic z swap
		//int wartosc = get(temp);
		//set(i, get(temp));
		//set(temp, get(i));
		swap(kopiec[i], kopiec[temp]);
		down(temp); //rekurencja
	}
}

ostream& operator<<(ostream& out, Heap& h)
{
	if (h.empty())
		return out;

	for (int i = 0; i < h.heap_size; i++)
	{
		out << h.kopiec[i] << " ";
	}
	return out;
}

class PriorityQueue 
{
private:
	Heap h; //korzystam z klasy Heap
public:
	PriorityQueue(int c); //tworzy pusty kopiec o pojemnosci c					
	bool empty(); //zwraca true, jesli kolejka jest pusta, false w przeciwnym razie
	bool full(); //zwraca true, jesli kolejka jest pelna, false w przeciwnym razie
	void insert(int x);		//wstawia element z priorytetem x
	int maximum(); 			//zwraca element z najwyzszym priorytetem
	void deleteMax();		//usuwa  element z najwyzszym priorytetem
	void del(int i);		//usuwa  element z pozycji i
	void increasePriority(int i);	//zwieksza priorytet elementu na pozycji i
	void decreasePriority(int i);	//zmniejsza priorytet elementu na pozycji i
	friend ostream& operator<<(ostream& out, PriorityQueue& q); //wyswietla kolejke na ekranie
};

PriorityQueue::PriorityQueue(int c)
{
	Heap temp(c);
	h = temp;
	//h = Heap(c);
}

bool PriorityQueue::empty()
{
	if (h.empty())
		return true;
	return false;
}

bool PriorityQueue::full()
{
	if (h.full())
		return true;
	return false;
}

void PriorityQueue::insert(int x)
{
	if (empty()) //wystarczy tylko !full()
	{
		h.set(0, x); //jesli kopiec jest pusty, to tworze korzen i nie musze przywracac wlasnosci kopca
		h.setHeapSize(1);
	}
	else
	{
		if (!full())
		{
			h.set(h.getSize(), x); //wstawiam nowy element jako ostatni lisc
			h.setHeapSize(h.getSize() + 1); //zwiekszam heap_size
			h.up(h.getSize() - 1); //przywracam wlasnosc kopca metoda wynurzania
		}
	}
}

int PriorityQueue::maximum()
{
	if (!empty())
		return h.get(0); //zwracam wartosc z korzenia kopca
	return NULL;
}

void PriorityQueue::deleteMax()
{
	if (!empty())
	{
		h.set(0, h.get(h.getSize() - 1)); //ustawiam na miejscu ostatni lisci
		h.setHeapSize(h.getSize() - 1); //usuwam ostatni lisc poprzez zmniejszenie heap_size
		h.down(0); //przywracam wlasnosc kopca metoda zatapiania
	}
}

void PriorityQueue::del(int i)
{
	if (i >= 0 && i < h.getSize())
	{
		if (2 * i + 2 > h.getSize()) //wtedy i jest lisciem
		{
			if(i != h.getSize() - 1)
				h.set(i, h.get(h.getSize() - 1));
			h.setHeapSize(h.getSize() - 1);
			return;
		}
		else
		{
			h.set(i, h.get(h.getSize() - 1));
			h.setHeapSize(h.getSize() - 1);
			h.down(i);
		}
	}

	//dziala zle w niektorych przpadkach
	/**if (i >= 0 && i < h.getSize())
	{
		//ustawiam nowy korzen jako ostatni lisci i na pozycji i daje stary korzen i przywracam wlasnosc kopca
		h.set(i, h.get(0));
		h.set(0, h.get(h.getSize() - 1));
		h.down(0); //zatapianie nowego korzenia
		h.up(i); //zatapianie od miejsca, w którym jest stary korzen
		h.setHeapSize(h.getSize() - 1);
	}**/
}

void PriorityQueue::increasePriority(int i)
{
	if (!empty())
	{
		h.set(i, h.get(i) + 1); //zwiekszam priorytet
		h.up(i); //trzeba przywrocic wlasnosc kopca
	}
}

void PriorityQueue::decreasePriority(int i)
{
	if (!empty())
	{
		h.set(i, h.get(i) - 1); //zmniejszam priorytet
		h.down(i); //trzeba przywrocic wlasnosc kopca
	}
}

ostream& operator<<(ostream& out, PriorityQueue& q)
{
	if (q.empty())
		return out;
	for (int i = 0; i < q.h.getSize(); i++)
	{
		out << q.h.get(i) << " ";
	}
	out << endl;
	return out;
}

int main()
{
	/**Heap kopiec = Heap();

	cout << kopiec << endl;

	kopiec.set(8, 15);

	kopiec.up(8);

	cout << kopiec << endl;

	kopiec.set(1, 1);

	kopiec.down(1);

	cout << kopiec << endl;**/

	PriorityQueue queue = PriorityQueue(10);

	cout << queue << endl;

	queue.insert(9);
	queue.insert(5);
	queue.insert(1);
	queue.insert(6);
	queue.insert(3);
	queue.insert(12);
	queue.del(2);
	//queue.del(3);
	//queue.increasePriority(3);
	//queue.increasePriority(3);
	queue.decreasePriority(1);
	queue.decreasePriority(1);

	cout << queue << endl;

	while(!queue.empty()) {
		cout << queue.maximum() << " ";
		queue.deleteMax();
	}
	cout << endl;

	return 0;
}