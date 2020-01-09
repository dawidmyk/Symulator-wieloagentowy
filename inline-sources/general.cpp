
//klasa szablonowa opakowująca wskaźniki i nic z nimi nie robiąca
//służąca do obchodzenia się z obiektami których właścicielem jest
//singleton Graph, które istnieją na stercie



template <typename kind>
inline kind & general_ptr<kind>::operator * () const { //operator dereferencji
	return *object; //zwraca referencję
}

template <typename kind>
inline kind * general_ptr<kind>::operator -> () const { //zasady techniczne języka
	return object; //mówią że operator -> musi zwracać wskaźnik
}
//dobieranie się dwoma powyższymi metodami mogłoby rzucać wyjątek
//gdy w środku jest null
//szczególnie że tak jesteśmy zdani na segfault, jeszcze zależny
//od wyścigu wątków
//więc ten segfault może nie wystąpić w debugerze
//ale nie mam narazie pomysłu gdzie taki wyjątek łapać

template <typename kind>
inline bool general_ptr<kind>::isEmpty() const { //czasem trzeba sprawdzać czy nie ma nulla
	//w środku, a jeśli jest, to powstrzymać się przed sięganiem
	//wgłąb
	return object == nullptr;
}

template <typename kind>
inline general_ptr<kind>::operator bool() const { //operator (niejawnej) konwersji
	return !isEmpty();
}

template <typename kind>
inline bool general_ptr<kind>::operator == (const general_ptr<kind> & another) const {
	return object == another.object;
} //te operatory porównania używane gdzieś tam np. w chooseExcept

template <typename kind>
inline bool general_ptr<kind>::operator != (const general_ptr<kind> & another) const {
	return ! operator == (another);
}

template <typename kind>
inline kind * general_ptr<kind>::get() const { //getter
	return object;
}

template <typename kind>
inline void general_ptr<kind>::set(kind * object) { //setter
	this->object = object;
}

template <typename kind>
inline general_ptr<kind>::general_ptr(): object(nullptr) {} //używany jawnie przy zwracaniu nulla
//z funkcji gdy coś tam jest nie tak

template <typename kind>
inline general_ptr<kind>::general_ptr(kind * object): object(object) {} //konstruktor ze wskaźnika

//zwykłego, przydaje się przy konstrukcji z this

template <typename kind>
inline general_ptr<kind>::general_ptr(const std::unique_ptr<kind> & object): object(object.get()) {}


template <typename kind>
inline general_ptr<kind> & general_ptr<kind>::operator = (const std::unique_ptr<kind> & object) {
	this->object = object.get();
	return *this;
} //w Graph siedzi unique_ptr a my musimy zrobić general_ptr żeby
//go używać poza Graphem

//standardowy model przeciążania operatora = zakłada zwracanie referencji
//na bieżący obiekt by można było chainować
//a = b = c = d;
	
