#pragma once
#include <memory>
//klasa szablonowa opakowująca wskaźniki i nic z nimi nie robiąca
//służąca do obchodzenia się z obiektami których właścicielem jest
//singleton Graph, które istnieją na stercie
template <typename kind>
class general_ptr {
	kind * object;
	public:
	kind & operator * () const { //operator dereferencji
		return *object; //zwraca referencję
	}
	kind * operator -> () const { //zasady techniczne języka
		return object; //mówią że operator -> musi zwracać wskaźnik
	}
	//dobieranie się dwoma powyższymi metodami mogłoby rzucać wyjątek
	//gdy w środku jest null
	//szczególnie że tak jesteśmy zdani na segfault, jeszcze zależny
	//od wyścigu wątków
	//więc ten segfault może nie wystąpić w debugerze
	//ale nie mam narazie pomysłu gdzie taki wyjątek łapać
	bool isEmpty() const { //czasem trzeba sprawdzać czy nie ma nulla
		//w środku, a jeśli jest, to powstrzymać się przed sięganiem
		//wgłąb
		return object == nullptr;
	}
	operator bool() const { //operator (niejawnej) konwersji
		return !isEmpty();
	}
	bool operator == (const general_ptr<kind> & another) const {
		return object == another.object;
	} //te operatory porównania używane gdzieś tam np. w chooseExcept
	bool operator != (const general_ptr<kind> & another) const {
		return ! operator == (another);
	}
	kind * get() const { //getter
		return object;
	}
	void set(kind * object) { //setter
		this->object = object;
	}
	
	general_ptr(): object(nullptr) {} //używany jawnie przy zwracaniu nulla
	//z funkcji gdy coś tam jest nie tak
	general_ptr(kind * object): object(object) {} //konstruktor ze wskaźnika
	//zwykłego, przydaje się przy konstrukcji z this
	general_ptr(const std::unique_ptr<kind> & object): object(object.get()) {}
	general_ptr(const general_ptr<kind> & another) = default;
	//default po prostu skopiuje wszystkie pola odpowiednimi operatorami
	//a tu jedynym polem jest wskaźnik i go się po prostu kopiuje
	//bez żadnych metod
	general_ptr & operator = (const general_ptr<kind> & another) = default;
	general_ptr & operator = (general_ptr<kind> && another) = default;
	general_ptr & operator = (const std::unique_ptr<kind> & object) {
		this->object = object.get();
		return *this;
	} //w Graph siedzi unique_ptr a my musimy zrobić general_ptr żeby
	//go używać poza Graphem
	
	//standardowy model przeciążania operatora = zakłada zwracanie referencji
	//na bieżący obiekt by można było chainować
	//a = b = c = d;
	~general_ptr() = default;
	//nic nie trzeba załatwiać przy zakończeniu życia tego general_ptr
	//nie wiem nawet czy powyższy destruktor jest potrzebny
};
