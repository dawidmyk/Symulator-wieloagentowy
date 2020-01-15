#ifndef GENERAL
#define GENERAL

#include <memory>
//klasa szablonowa opakowująca wskaźniki i nic z nimi nie robiąca
//służąca do obchodzenia się z obiektami których właścicielem jest
//singleton Graph, które istnieją na stercie
template <typename kind>
class general_ptr {
	kind * object;
	public:
	kind & operator * () const;
	kind * operator -> () const;
	//dobieranie się dwoma powyższymi metodami mogłoby rzucać wyjątek
	//gdy w środku jest null
	//szczególnie że tak jesteśmy zdani na segfault, jeszcze zależny
	//od wyścigu wątków
	//więc ten segfault może nie wystąpić w debugerze
	//ale nie mam narazie pomysłu gdzie taki wyjątek łapać
	bool isEmpty() const;
	operator bool() const;
	bool operator == (const general_ptr<kind> & another) const;
	//te operatory porównania używane gdzieś tam np. w chooseExcept
	bool operator != (const general_ptr<kind> & another) const;
	kind * get() const;
	void set(kind * object);
	
	general_ptr(); //używany jawnie przy zwracaniu nulla
	//z funkcji gdy coś tam jest nie tak
	general_ptr(kind * object); //konstruktor ze wskaźnika
	//zwykłego, przydaje się przy konstrukcji z this
	general_ptr(const std::unique_ptr<kind> & object);
	general_ptr(const general_ptr<kind> & another) = default;
	//defaulty zostawiam w headerach
	
	//default po prostu skopiuje wszystkie pola odpowiednimi operatorami
	//a tu jedynym polem jest wskaźnik i go się po prostu kopiuje
	//bez żadnych metod
	general_ptr<kind> & operator = (const general_ptr<kind> & another) = default;
	general_ptr<kind> & operator = (general_ptr<kind> && another) = default;
	general_ptr<kind> & operator = (const std::unique_ptr<kind> & object);
	//w Graph siedzi unique_ptr a my musimy zrobić general_ptr żeby
	//go używać poza Graphem
	
	//standardowy model przeciążania operatora = zakłada zwracanie referencji
	//na bieżący obiekt by można było chainować
	//a = b = c = d;
	~general_ptr() = default;
	//nic nie trzeba załatwiać przy zakończeniu życia tego general_ptr
	//nie wiem nawet czy powyższy destruktor jest potrzebny
	
};

#include "inline_general.cpp"
#endif
