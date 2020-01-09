template <typename kind>
	general_ptr<kind>::general_ptr(const general_ptr<kind> & another) = default;
	//default po prostu skopiuje wszystkie pola odpowiednimi operatorami
	//a tu jedynym polem jest wskaźnik i go się po prostu kopiuje
	//bez żadnych metod
	
	template <typename kind>
	general_ptr & general_ptr<kind>::operator = (const general_ptr<kind> & another) = default;
	
	template <typename kind>
	general_ptr & general_ptr<kind>::operator = (general_ptr<kind> && another) = default;
	
	template <typename kind>
	~general_ptr<kind>::general_ptr() = default;
	//nic nie trzeba załatwiać przy zakończeniu życia tego general_ptr
	//nie wiem nawet czy powyższy destruktor jest potrzebny
	
	//Jakby jednak tu te defaulty były potrzebne
};
