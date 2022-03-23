/*
* ПРАВИЛА:
Вам нужно собрать три колоды карт каждая из которых "караван", общим номиналом не меньше 21  и не больше 26 очков.
Караван дожен быть одной масти.

В игре есть карты действия:

Король - умножает количество очков каравана
Дама - меняет масть 
Валет - сносит караван*/

/*В организации логики игры я специально сделал массив объектов и организовал действия при помощи перегрузки операторов,
на мой вгляд в дальнешем это позволяет более гибко проработаь механику игрового процесса и самостоятельно регулировать 
действия с объектами(например при сложении объектов сохранять один из параметров объекта неизменным), а так же в дальнейшем прицепить к объектам графику*/


#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include <stdlib.h>

using namespace std;
class Card
{
protected:
	string cardname;
	string cardsuit;
	int cardpower;
	static int count;
public:
	Card()
	{
		cardname = "Name ";
		cardsuit = "none ";
		cardpower = 0;
	}
	Card(const string& name,const string& suit,const int& power)
	{
		cardname = name;
		cardsuit = suit;
		cardpower = power;
	}
	void Getinfo()
	{	
		cout << " Card " << cardname << endl; 
		cout << " Suit " << cardsuit << endl; 
		cout << " Power " << cardpower << endl;
		cout << "_______________________" << endl;
	}
	string GetCardName()
	{
			return cardname;
	}
	string GetCardSuit()
	{
			return cardsuit;
	}
	int GetCardPower()
	{
			return cardpower;
	}
	int SetCardPower(int m_cardpower)
	{
		cardpower = m_cardpower;
		return 0;
	}
	Card operator=(const Card& deck) {
		this->cardname = deck.cardname;
		this->cardsuit = deck.cardsuit;
		this->cardpower = deck.cardpower;
		return *this;
	}
	Card operator +=(const Card& other)
	{
		
		this->cardname += other.cardname;
		this->cardsuit = other.cardsuit;
		this->cardpower += other.cardpower;
		return *this;
	}
	Card operator *=(const Card& other)
	{
		
		this->cardname += other.cardname;
		this->cardsuit = other.cardsuit;
		this->cardpower *= other.cardpower;
		return *this;
	}
	Card operator +(const Card& other)
	{
		Card caravan;
		caravan.cardname = cardname + other.cardname;
		caravan.cardsuit = other.cardsuit;
		caravan.cardpower = cardpower + other.cardpower;
		return caravan;
	}
	bool operator <=(const Card& other)
	{
		return cardname <= other.cardname && cardsuit <= other.cardsuit && cardpower <= other.cardpower;
	}
	bool operator >=(const Card& other)
	{
		return cardname >= other.cardname && cardsuit >= other.cardsuit && cardpower >= other.cardpower;
	}
	bool operator ==(const Card& other)
	{
		return cardname == other.cardname && cardsuit == other.cardsuit && cardpower == other.cardpower;
	}
	bool operator !=(const Card& other)
	{
		return cardname != other.cardname && cardsuit != other.cardsuit && cardpower != other.cardpower;
	}
	~Card()
	{
	//cout << "memory clear" <<count++<< endl;
	} 
	};
int Card::count = 1;

void TakeCards( Card *hand, Card *deck, Card* zero) // Функция взятия карт в руки
{
	int a;
	bool alreadyThere;
	for (int i = 0; i <8; )
	{
		alreadyThere = false;
		int a = 0 + rand() % 53;
		for (int j = 0; j < i; j++)
		{
			if (hand[j] == deck[a] || deck[a] == zero[0] )
			{
				alreadyThere = true;
				break;
			}
		}
		if (!alreadyThere)
		{
			
			hand[i] = deck[a];
			deck[a] = zero[0];
			i++;
		}
	}
}
void TakeCardsForGamedeck(Card* deck, Card* zero, Card* gamedeck) // функция перемешивания карт и создание игровой колоды
{
	int p;
	bool alreadyThere;
	for (int i = 0; i < 46; )
	{
		alreadyThere = false;
		int p = 0 + rand() % 54;
		for (int j = 0; j < i; j++)
		{
			if (gamedeck[j] == deck[p] || deck[p] == zero[0])
			{
				alreadyThere = true;
				break;
			}
		}
		if (!alreadyThere)
		{
			gamedeck[i] = deck[p];
			i++;
		}
	}
}
/*void TakeFromFromGameDeck(Card* hand, Card* gamedeck)
{
	int i = 0;
	do 
	{
		hand[8] = gamedeck[i];
		i++;
	}
	while (i < 46);
		
}*/

int main()
{
	srand(time(NULL));
	int cardrotation = 0; // переменная для итерации карт в игровой колоде
	int cardnumber = 0; // переменная для выбора карты из руки
	int switch_caravan = 0; //переменная для выбора каравана
	char answ ='n'; 
	char confirm ='n';
	Card gamedeck[54]; // игровая колода
	Card zero[1]; // объект нулевой карты
	Card caravan1; // караван 1 место собирание каравана карт
	Card caravan2; // караван 2 место собирание каравана карт
	Card caravan3; // караван 3 место собирание каравана карт
	Card hand[9]{}; // место для карт находящихся в руке игрока

	do // блок в котором происходит формирование карт в руке и в игровой колоде
	{
		Card deck[54] = { 
		Card("ACE ","Diamonds ",1),		Card("ACE ","Hearts ",1),	Card("ACE ","Clubs ",1),	Card("ACE ","Spades ",1),
		Card("King ","Diamonds ",2),	Card("King ","Hearts ",2),	Card("King ","Clubs ",2),	Card("King ","Spades ",2),
		Card("Queen ","Diamonds ",1),	Card("Queen ","Hearts ",1),Card("Queen ","Clubs ",1),	Card("Queen ","Spades ",1),
		Card("Jack ","Diamonds ",0),	Card("Jack ","Hearts ",0),	Card("Jack ","Clubs ",0),	Card("Jack ","Spades ",0),
		Card("Ten ","Diamonds ",10),	Card("Ten ","Hearts ",10),	Card("Ten ","Clubs ",10),	Card("Ten ","Spades ",10),
		Card("Nine ","Diamonds ",9),	Card("Nine ","Hearts ",9),	Card("Nine ","Clubs ",9),	Card("Nine ","Spades ",9),
		Card("Eigth ","Diamonds ",8),	Card("Eigth ","Hearts ",8),	Card("Eigth ","Clubs ",8),	Card("Eigth ","Spades ",8),
		Card("Seven ","Diamonds ",7),	Card("Seven ","Hearts ",7),	Card("Seven ","Clubs ",7),	Card("Seven ","Spades ",7),
		Card("Six ","Diamonds ",6),		Card("Six ","Hearts ",6),	Card("Six ","Clubs ",6),	Card("Six ","Spades ",6),
		Card("Five ","Diamonds ",5),	Card("Five ","Hearts ",5),	Card("Five ","Clubs ",5),	Card("Five ","Spades ",5),
		Card("Four ","Diamonds ",4),	Card("Four ","Hearts ",4),	Card("Four ","Clubs ",4),	Card("Four ","Spades ",4),
		Card("Three ","Diamonds ",3),	Card("Three ","Hearts ",3),	Card("Three ","Clubs ",3),	Card("Three ","Spades ",3),
		Card("Two ","Diamonds ",2),		Card("Two ","Hearts ",2),	Card("Two ","Clubs ",2),	Card("Two ","Spades ",2),
		Card("JOKER ","RED ",1),
		Card("JOKER ","BLACK ",1) };
		system("CLS");
		TakeCards(hand, deck, zero);
		TakeCardsForGamedeck(deck, zero, gamedeck);
			for (int k = 0; k < 8; k++)
			{
				hand[k].Getinfo();
			}
		 
		cout << "Cards mixed,ready? (y - for start/onther key for remix cards)" << endl;
		cin >> answ;
		
	} while (answ != 'y');
	
	do // начало игрового процесса
	{
		cout << "Choose card 0-7, 8 - take from deck" << endl;
		cin >> cardnumber;
		if (cardnumber != 8) 
		{
			cout << "Choose caravan 1 or 2,3" << endl;
			cin >> switch_caravan;
			switch (switch_caravan)
			{
				case 1:
					if (caravan1.GetCardSuit() == "none " || caravan1.GetCardSuit() == hand[cardnumber].GetCardSuit() && hand[cardnumber].GetCardName() != "Jack " && hand[cardnumber].GetCardName() != "King ")
					{
						caravan1 += hand[cardnumber];
						hand[cardnumber] = zero[0];
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}
					}
					else if (caravan1.GetCardSuit() == "none " || caravan1.GetCardSuit() == hand[cardnumber].GetCardSuit() && hand[cardnumber].GetCardName() == "King ")
					{
						caravan1 *= hand[cardnumber];
						hand[cardnumber] = zero[0];
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}

					}
					else if (caravan1.GetCardSuit() == "none " || hand[cardnumber].GetCardName() == "Queen ")
					{
						caravan1 += hand[cardnumber];
						hand[cardnumber] = zero[0];
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}
					}
					else if (caravan1.GetCardSuit() == "none " || caravan1.GetCardSuit() == hand[cardnumber].GetCardSuit() || hand[cardnumber].GetCardName() == "Jack ")
					{
						caravan1 = hand[cardnumber];
						hand[cardnumber] = zero[0];
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}
					}
					else 
					{
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}
					} exit; 
					break;
				case 2:
					if (caravan2.GetCardSuit() == "none " || caravan2.GetCardSuit() == hand[cardnumber].GetCardSuit() && hand[cardnumber].GetCardName() != "Jack " && hand[cardnumber].GetCardName() != "King ")
					{
						caravan2 += hand[cardnumber];
						hand[cardnumber] = zero[0];
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}
					}
					else if (caravan2.GetCardSuit() == "none " || caravan2.GetCardSuit() == hand[cardnumber].GetCardSuit() && hand[cardnumber].GetCardName() != "King ")
					{
						caravan2 *= hand[cardnumber];
						hand[cardnumber] = zero[0];
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}

					}
					else if (caravan2.GetCardSuit() == "none " || hand[cardnumber].GetCardName() == "Queen ")
					{
						caravan2 += hand[cardnumber];
						hand[cardnumber] = zero[0];
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}
					}
					else if (caravan2.GetCardSuit() == "none " || caravan2.GetCardSuit() == hand[cardnumber].GetCardSuit() || hand[cardnumber].GetCardName() == "Jack ")
					{
						caravan2 = hand[cardnumber];
						hand[cardnumber] = zero[0];
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}
					}
					else 
					{
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}
					} exit;
					break;
				case 3:
					if (caravan3.GetCardSuit() == "none " || caravan3.GetCardSuit() == hand[cardnumber].GetCardSuit() && hand[cardnumber].GetCardName() != "Jack " && hand[cardnumber].GetCardName() != "King ")
					{
						caravan3 += hand[cardnumber];
						hand[cardnumber] = zero[0];
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}
					}
					else if (caravan3.GetCardSuit() == "none " || caravan3.GetCardSuit() == hand[cardnumber].GetCardSuit() && hand[cardnumber].GetCardName() != "King ")
					{
						caravan3 *= hand[cardnumber];
						hand[cardnumber] = zero[0];
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}

					}
					else if (caravan3.GetCardSuit() == "none " || hand[cardnumber].GetCardName() == "Queen ")
					{
						caravan3 += hand[cardnumber];
						hand[cardnumber] = zero[0];
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}
					}
					else if (caravan3.GetCardSuit() == "none " || caravan3.GetCardSuit() == hand[cardnumber].GetCardSuit() || hand[cardnumber].GetCardName() == "Jack ")
					{
						caravan3 = hand[cardnumber];
						hand[cardnumber] = zero[0];
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						}
					}
					else
					{
						system("CLS");
						for (int k = 0; k < 8; k++)
						{
							hand[k].Getinfo();
						} 
					} exit;
					break;
					default: exit;
					break;
			}
		}
		else
		{ 
			do
			{
				hand[8] = gamedeck[cardrotation];
				cardrotation++;
				system("CLS");
				for (int k = 0; k < 8; k++)
				{
					hand[k].Getinfo();
				}
				cout << "This card from game deck " << endl;
				cout << endl;
				hand[8].Getinfo();
				cout << "confirm?" << endl;
				cin >> confirm;
			} while (confirm != 'y');

			cout << "Choose caravan 1 or 2,3" << endl;
			cin >> switch_caravan;

			switch (switch_caravan)
			{
			case 1:
				if (caravan1.GetCardSuit() == "none " || caravan1.GetCardSuit() == hand[cardnumber].GetCardSuit() && hand[cardnumber].GetCardName() != "Jack " && hand[cardnumber].GetCardName() != "King ")
				{
					caravan1 += hand[cardnumber];
					hand[cardnumber] = zero[0];
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}
				}
				else if (caravan1.GetCardSuit() == "none " || caravan1.GetCardSuit() == hand[cardnumber].GetCardSuit() && hand[cardnumber].GetCardName() != "King ")
				{
					caravan1 *= hand[cardnumber];
					hand[cardnumber] = zero[0];
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}

				}
				else if (caravan1.GetCardSuit() == "none " || hand[cardnumber].GetCardName() == "Queen ")
				{
					caravan1 += hand[cardnumber];
					hand[cardnumber] = zero[0];
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}
				}
				else if (caravan1.GetCardSuit() == "none " || caravan1.GetCardSuit() == hand[cardnumber].GetCardSuit() || hand[cardnumber].GetCardName() == "Jack ")
				{
					caravan1 = hand[cardnumber];
					hand[cardnumber] = zero[0];
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}
				}
				else
				{
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}
				} exit;
				break;
			case 2:
				if (caravan2.GetCardSuit() == "none " || caravan2.GetCardSuit() == hand[cardnumber].GetCardSuit() && hand[cardnumber].GetCardName() != "Jack " && hand[cardnumber].GetCardName() != "King ")
				{
					caravan2 += hand[cardnumber];
					hand[cardnumber] = zero[0];
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}
				}
				else if (caravan2.GetCardSuit() == "none " || caravan2.GetCardSuit() == hand[cardnumber].GetCardSuit() && hand[cardnumber].GetCardName() != "King ")
				{
					caravan2 *= hand[cardnumber];
					hand[cardnumber] = zero[0];
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}

				}
				else if (caravan2.GetCardSuit() == "none " || hand[cardnumber].GetCardName() == "Queen ")
				{
					caravan2 += hand[cardnumber];
					hand[cardnumber] = zero[0];
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}
				}
				else if (caravan2.GetCardSuit() == "none " || caravan2.GetCardSuit() == hand[cardnumber].GetCardSuit() || hand[cardnumber].GetCardName() == "Jack ")
				{
					caravan2 = hand[cardnumber];
					hand[cardnumber] = zero[0];
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}
				}
				else 
				{
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}
				} exit;
				break;
			case 3:
				if (caravan3.GetCardSuit() == "none " || caravan3.GetCardSuit() == hand[cardnumber].GetCardSuit() && hand[cardnumber].GetCardName() != "Jack " && hand[cardnumber].GetCardName() != "King ")
				{
					caravan3 += hand[cardnumber];
					hand[cardnumber] = zero[0];
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}
				}
				else if (caravan3.GetCardSuit() == "none " || caravan3.GetCardSuit() == hand[cardnumber].GetCardSuit() && hand[cardnumber].GetCardName() != "King ")
				{
					caravan3 *= hand[cardnumber];
					hand[cardnumber] = zero[0];
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}

				}
				else if (caravan3.GetCardSuit() == "none " || hand[cardnumber].GetCardName() == "Queen ")
				{
					caravan3 += hand[cardnumber];
					hand[cardnumber] = zero[0];
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}
				}
				else if (caravan3.GetCardSuit() == "none " || caravan3.GetCardSuit() == hand[cardnumber].GetCardSuit() || hand[cardnumber].GetCardName() == "Jack ")
				{
					caravan3 = hand[cardnumber];
					hand[cardnumber] = zero[0];
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}
				}
				else 
				{
					system("CLS");
					for (int k = 0; k < 8; k++)
					{
						hand[k].Getinfo();
					}
				} exit;
				break;
				default: exit;
				break;
			}
		}
		cout << "*************************" << endl;
		cout << "*caravan score:         *" << endl;
		cout << "*************************" << endl;
		cout << endl;
		cout << "caravan 1: " << endl; caravan1.Getinfo();
		cout << "caravan 2: " << endl; caravan2.Getinfo();
		cout << "caravan 3: " << endl; caravan3.Getinfo();
	}
	while 
		  ((caravan1.GetCardPower() <= 21 || caravan1.GetCardPower() >= 26) 
	    && (caravan2.GetCardPower() <= 21 || caravan2.GetCardPower() >= 26)
		&& (caravan3.GetCardPower() <= 21 || caravan2.GetCardPower() >= 26));
	{
		cout << "Caravan stoped" << endl;
	}
}

/*for (int k = 0; k < 54; k++)
		   {
			   cout << " **" << endl;
			   gamedeck[k].Getinfo();
		   }*/
/*int a;
	bool alreadyThere;
	for (int i = 0; i < 8; )
	{
		alreadyThere = false;
		int a = 0 + rand() % 53;

		for (int j = 0; j < i; j++)
		{
			if (hand[j] == deck[a])
			{
				alreadyThere = true;
				break;
			}
		}
		if (!alreadyThere)
		{
			hand[i] = deck[a];
			i++;
		}
	}
	*/

/*Card CPUhand[8]{};
TakeCards(CPUhand, deck);
for (int k = 0; k < 8; k++)
{
	cout << "_CPUcard_" << endl;
	CPUhand[k].Getinfo();
}*/

