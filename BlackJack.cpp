#include<windows.h> //for Sleep()(windows)
#include<iostream> //for cout and endl
#include<time.h> //for time function
#include<random>  //for default_random_engine()
#include<algorithm> //for shuffle()
using namespace std;

string Suits[] = {"Spades","Clubs","Diamonds","Hearts"};
string Ranks[] = {"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};

void clrscr()
{
  system("cls");
}

void delay(int n)
{
  Sleep(n*1000);
}

class Card
{
private:
  string Suit;
  string Rank;
public:
  Card(){ }
  Card(string s, string r)
  {
    Suit = s;
    Rank = r;
  }
  Card(const Card &crd)
  {
    Suit = crd.Suit;
    Rank = crd.Rank;
  }
  void display()
  {
    cout<<Rank<<" of "<<Suit<<endl;
  }
  void operator=(const Card &crd)
  {
    Suit = crd.Suit;
    Rank = crd.Rank;
  }
  int value()
  {
    if(Rank=="Ace") return 1;
    if(Rank=="Two") return 2;
    if(Rank=="Three") return 3;
    if(Rank=="Four") return 4;
    if(Rank=="Five") return 5;
    if(Rank=="Six") return 6;
    if(Rank=="Seven") return 7;
    if(Rank=="Eight") return 8;
    if(Rank=="Nine") return 9;
    if(Rank=="Ten") return 10;
    if(Rank=="Jack") return 10;
    if(Rank=="Queen") return 10;
    if(Rank=="King") return 10;
    return 0;
  }
};

int sum(Card *hand,int len)
{
  int s=0;
  for(int i=0;i<len;i++)
  {
    s+=hand[i].value();
  }
  return s;
}

class Deck
{
private:
  Card all_cards[52] = {};
  static int indx;
  int index=0;
public:
  Deck()
  {
    for(int i=0;i<4;i++)
    {
      for(int j=0;j<13;j++)
      {
        Card c(Suits[i],Ranks[j]);
        all_cards[index] = c;
        index+=1;
      }
    }
  }
  void shuffled()
  {
    srand(time(0));
    int n = rand()%52;
    shuffle(all_cards, all_cards + 52, default_random_engine(n));
  }
  void display()
  {
    for(int i=indx;i<52;i++)
    {
      all_cards[i].display();
    }
  }
  Card dealOne()
  {
    Card dealt_card = all_cards[indx];
    indx+=1;
    return dealt_card;
  }
};

int Deck::indx = 0;

class Person
{
protected:
  Card hand[12]={};
  int index =0;
public:
  void addOne(const Card &c)
  {
    hand[index] = c;
    index+=1;
  }
  virtual void show_cards()
  {
    cout<<"Person has the following cards: \n";
    for(int i=0;i<index;i++)
      hand[i].display();
  }
  int sum_of_hand()
  {
    int s = sum(hand,index);
    return s;
  }
};

class Dealer: public Person
{
public:
  void show_cards()
  {
    cout<<"Dealer has the following cards: \n";
    for(int i=0;i<index;i++)
      hand[i].display();
  }
};


class Player: public Person
{
public:
  void show_cards()
  {
    cout<<"You have the following cards: \n";
    for(int i=0;i<index;i++)
      hand[i].display();
  }
};


bool Over21(Person &p)
{
  if(p.sum_of_hand()>21)
    return true;
  return false;
}

void players_turn(Person &player, Deck &deck, bool *game_over)
{
  while(true)
  {
    clrscr();
    char choice[10];
    int c;
    char num[3] = {'0','1','2'};
    player.show_cards();
    try
    {
      cout<<"\nEnter your choice:\n1.Hit\n2.Stay\n=>";
      cin>>choice;
      if(strlen(choice)==1)
      {
        bool matched = false;
        for(int i=1;i<=2;i++)
        {
          if(choice[0]==num[i])
          {
            c=i;
            matched = true;
            break;
          }
        }
        if(!matched)
          throw 'n';
        if(c==1)
          {
            cout<<"\nDealing one card..\n";
            delay(1);
            player.addOne(deck.dealOne());
            if(Over21(player))
            {
              clrscr();
              player.show_cards();
              cout<<"\nYou have BUSTED!! Dealer WINS\n\n";
              *game_over = true;
              break;
            }
          }
        else if(c==2)
        {
          cout<<"\nDealer's Turn\n";
          delay(1);
          break;
        }
      }
      else
        throw 'n';
    }
    catch(char)
    {
      cout<<"\nInvalid input!! Try again\n";
      delay(1);
    }
  }
}

void dealers_turn(Person &dealer, Deck deck, bool *game_over)
{
  while(true && !(*game_over))
  {
    clrscr();
    dealer.show_cards();
    cout<<"\nWaiting for dealer's choice...\n";
    delay(2);
    if(dealer.sum_of_hand()<=11)
    {
      cout<<"\nDealer has decided to deal one card\n";
      delay(2);
      dealer.addOne(deck.dealOne());
      dealer.show_cards();
      continue;
    }
    else if(dealer.sum_of_hand()<14)
    {
      srand(time(0));
      int x = rand()%6;
      if(x!=2 && x!=3)
      {
        cout<<"\nDealer has decided to deal one card\n";
        delay(2);
        dealer.addOne(deck.dealOne());
        if(Over21(dealer))
        {
          clrscr();
          dealer.show_cards();
          cout<<"\nDealer has BUSTED!! You WIN\n\n";
          *game_over = true;
          break;
        }
      }
      else
      {
        cout<<"\nDealer has stayed with his hand\n";
        delay(2);
        break;
      }
    }
    else if(dealer.sum_of_hand()<17)
    {
      srand(time(0));
      int x = rand()%6;
      if(x%2==0)
      {
        cout<<"\nDealer has decided to deal one card\n";
        delay(2);
        dealer.addOne(deck.dealOne());
        if(Over21(dealer))
        {
          clrscr();
          dealer.show_cards();
          cout<<"\nDealer has BUSTED!! You WIN\n\n";
          *game_over = true;
          break;
        }
      }
      else
      {
        cout<<"\nDealer has stayed with his hand\n";
        delay(2);
        break;
      }
    }
    else if(dealer.sum_of_hand()<=20)
    {
      srand(time(0));
      int x = rand()%6;
      if(x==4)
      {
        cout<<"\nDealer has decided to deal one card\n";
        delay(2);
        dealer.addOne(deck.dealOne());
        if(Over21(dealer))
        {
          clrscr();
          dealer.show_cards();
          cout<<"\nDealer has BUSTED!! You WIN\n\n";
          *game_over = true;
          break;
        }
      }
      else
      {
        cout<<"\nDealer has stayed with his hand\n";
        delay(2);
        break;
      }
    }
    else
    {
      cout<<"\nDealer has stayed with his hand\n";
      delay(2);
      break;
    }
  }
}

void game(Deck &deck, Person &player, Person &dealer)
{
  bool game_over = false;
  for(int i=0;i<4;i++)
  {
    if(i%2==0)
      player.addOne(deck.dealOne());
    else
      dealer.addOne(deck.dealOne());
  }
  players_turn(player,deck,&game_over);
  dealers_turn(dealer,deck,&game_over);
  if(!game_over)
  {
    clrscr();
    player.show_cards();
    cout<<"\n\n";
    dealer.show_cards();
    cout<<"\n\n";
    cout<<"By comparison of cards: \n";
    delay(3);
    if(player.sum_of_hand()>dealer.sum_of_hand())
      cout<<"You have won the game.\n\n";
    else if(player.sum_of_hand()<dealer.sum_of_hand())
      cout<<"Dealer has won the game.\n\n";
    else
      cout<<"Game drawn.\n\n";
  }
}

int main()
{
  string c;
  do
  {
    Deck *deck = new Deck;
    deck->shuffled();
    Player *player = new Player;
    Dealer *dealer = new Dealer;
    game(*deck,*player,*dealer);
    cout<<"Press Y to play again / Any other key to exit\n=>";
    cin>>c;
  }while(c=="y"||c=="Y");
    cout<<"\n\nEND OF PROGRAM\n\n";
    return 0;
}