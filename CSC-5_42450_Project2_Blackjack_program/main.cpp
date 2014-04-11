//=======================================
/*      B L A C K J A C K   1 0 1      */
/*      Name: Ezra Guinmapang          */
/*      Date: April 10, 2014           */
/*      Purpose: CSC-5-42450 Project 2 */
//=======================================

//Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Global variables and constants

//Class definitions
class Card{ //Card class - object representing a card - has a value, rank, and suit
    private:
        int c_Val; //stores the card Value
        char c_Rank, c_Suit; //stores the card Rank and Suit
    public:
        Card(); //Constructor for the card object
        Card(int, char, char); //stores the values of Card dealt or drawn
        ~Card(); //Destructor for Card;
        int getVal(); //to access the card Value
        char getSuit(); //to access the card Suit
        char getRank(); //to access the card Rank
        void SetVal(int); //sets the card Value
};
class Player{ //Player class - object representing the player - has a Hand, a draw count, and an ace count
    protected:
        int DrawCt, AceCt; //stores the number of cards drawn for this hand and number of aces for this hand
        Card c_Card, Hand[5]; //creates a hand of cards with a maximum of 5 cards to a hand
        int Total; //stores the total score of the player's hand
        string p_Name;
    public:
        Player(); //constructor for player object
        Player(string); //initializes the Player name
        ~Player(); //destructor for player object
        virtual void HoleCards(); // virtual function to be defined in derived class
        virtual void DrawCard(Card*, int &, int &); //virtual fucntion to be defined in derived class
        virtual void ScoreIt(); //scores a Player's hand
        void Greet(); //prints a greeting
        void ShowCard(); //prints the Rank and Suit of the Card drawn
        int Totalup(); //Returns the Total Score of a Player's hand
        /*int CardVal();
        char CardSt();
        char CardRk();*/
        string Name(); //outputs the Player name
};

class Dealer : public Player{ //special kind of Player instance - Deals and shuffles the cards
    public:
        Dealer(); //constructor for dealer object
        Dealer(string); //initializes the Dealer name
        ~Dealer(); //destructor for dealer object
        void HoleCards(); //print the Dealer's hole cards
        void DrawCard(Card*, int &, int &); //Draw a Card from the Shoe
        void ScoreIt(); //Score the Dealer starting hand
};
//Function prototypes
Card Deck(int); //Creates a Shoe of decks of Card objects
void Shuffle(Card*, int ); //Shuffles the Shoe
bool isBusted(int); //returns true if Player or Dealer score is Busted
bool isWinner(int, int); //returns true if Player score is >= Dealer score

//Execution begins HERE
int main(){
    //Declare variables
    int dChoice = 0, numDecks = 0; //stores the values for choice, number of decks to be used,
    int Ct = 0, t_Deck = 0; //number of cards in the shoe, and card count of the shoe
    char p_Hit; //stores whether a player chooses to draw a card or not
    string P_Name; //stores the name input for player
    //Prompt and input player's name
    cout << "Let's play blackjack!\n";
    cout << "What is your name? ";
    cin >> P_Name;
    //Create a Player instance
    Player *Player1 = new Player(P_Name);
    Player1 -> Greet();
    //Prompt and input number of decks to be used in the game
    cout << "How many decks did you want to use in the shoe? ";
    cin >> numDecks;
    Ct = 52 * numDecks; //Get the number of cards in the Shoe
    t_Deck = Ct - 1;
    Card Shoe[Ct]; //create the Shoe and populate it with the appropriate number of Cards
    Shuffle(Shoe, Ct); //shuffle the Shoe
    //Prompt and choose your Dealer
    cout << "Choose your Dealer:\n";
    cout << "1. Mack\n" << "2. Lila\n" << "3. Joe\n";
    cout << "Which dealer would you like? ";
    cin >> dChoice;
    switch(dChoice){
        case 1:{
            P_Name = "Mack";
            break;
        }
        case 2:{
            P_Name = "Lila";
            break;
        }
        case 3:{
            P_Name = "Joe";
            break;
        }
    }
    Dealer *Deal_X = new Dealer(P_Name); //pointer to the Dealer instance
    Player1-> DrawCard(Shoe, Ct, t_Deck); //Deal the Hole Cards from the Shoe to the Player
    Deal_X-> DrawCard(Shoe, Ct, t_Deck); //Deal the Hole Cards from the Shoe to the Dealer
    Player1-> DrawCard(Shoe, Ct, t_Deck);
    Deal_X-> DrawCard(Shoe, Ct, t_Deck); 
    Player1-> HoleCards(); //display the Player's Hole Cards
    Deal_X-> HoleCards(); //display the Dealer's Hole Cards
    cout << "Your hand is now at " << Player1-> Totalup() << endl; //display the value of Player's Hand
    //Prompt if Player wants to hit
    cout << "Would you like to get another card (Y/N)? ";
    cin >> p_Hit;
    while(p_Hit == 'Y' || p_Hit == 'y'){
        Player1-> DrawCard(Shoe, Ct, t_Deck); //Draws a Card from the Shoe
        Player1-> ShowCard(); //displays the Card drawn
        cout << "Your hand is now at " << Player1-> Totalup() << endl;
        //Check if Player is Busted. If not, Player may Hit again until Busted or max number of Cards is reached
        if(isBusted(Player1-> Totalup())){
            cout << Player1-> Name() << " is BUSTED!!!!\n";
            break;
        }
        cout << "Would you like to get another card (Y/N)? ";
        cin >> p_Hit;
    }
    if(!(isBusted(Player1-> Totalup()))){
        cout << Deal_X-> Name() << "\'s hand is now at " << Deal_X-> Totalup() << endl;
        while(Deal_X -> Totalup() < 17){ //This is the "Soft 17 rule: Dealer MUST hit until Hand value is 17 or higher
            cout << Deal_X-> Name() << " draws a card.\n";
            Deal_X-> DrawCard(Shoe, Ct, t_Deck); //Draws a Card from the Shoe
            Deal_X-> ShowCard(); //displays the Card drawn
            cout << Deal_X-> Name() << "\'s hand is now at " << Deal_X-> Totalup() << endl;
        }
        if(isBusted(Deal_X-> Totalup())) cout << Deal_X-> Name() << " is BUSTED!!!!\n";
        else cout << Deal_X-> Name() << " stays.\n";
    }
    //Compare Player Total and Dealer Total to determine the winner and output the appropriate name
    cout << ((isWinner(Player1-> Totalup(), Deal_X-> Totalup())) ? Player1-> Name() : Deal_X-> Name()) << " WINS!!!\n";
    delete Player1; //deletes the Plaeyr instance
    delete Deal_X; //deletes the Dealer instance
    return 0;
}
//Function definitions
//Populates one Deck of Cards in random order
Card Deck(int Ctr){
    char St, Rk;
    Card anDeck[52]; //array representing one deck of Cards
    int j = 0, v = 0; //iterators for the loops
    srand(time(0)); //seed the rand() function)
    //Populate the Deck
    for(int k = 0; k < 4; k++){
        switch(k){ //determines the Suit of each Card
            case 0: St = 'H'; break;
            case 1: St = 'D'; break;
            case 2: St = 'S'; break;
            case 3: St = 'C'; break;
        }
        for (int i = 1; i < 14; i++){
            switch(i){ //determines the Rank and the initial Value of each Card
                case 1:  Rk = 'A'; v = 11; break;
                case 10: Rk = 'T'; v = 10; break;
                case 11: Rk = 'J'; v = 10; break;
                case 12: Rk = 'Q'; v = 10; break;
                case 13: Rk = 'K'; v = 10; break;
                default: Rk = '0' + i; v = i; break;
            }
            //create a Card instance with Value of v, Suit of St, and Rank of Rk and store it in the Deck array
            anDeck[j] = Card(v, St, Rk); 
            j++; //This increments the Deck array index to store the next Card object created
        }
    }
    //Shuffles one Deck of Cards
    for (int m = 0; m < 52; m++){
        int nSwap1, nSwap2;
        nSwap1 = (rand() % 51);
        nSwap2 = (rand() % 51);
        swap(anDeck[nSwap1], anDeck[nSwap2]);
    }
    swap(anDeck[51], anDeck[34]);
    //Returns the Card object contained in the Deck array element Deck[Ctr]]
    return anDeck[Ctr];
}
//Shuffle the Shoe, which is made up of several Decks of Cards
void Shuffle(Card Shoe[], int Ct){
    do{
        //Get a  unique (to one deck) Card instance from the Deck array and store it in the Shoe array element Shoe[Ct]
        //until the Shoe array is full
        for(int Ctr = 0; Ctr < 52; Ctr++){ 
            Ct--; //decrement Ct (number of Cards in the Shoe)
            Shoe[Ct] = Deck(Ctr);
            cout << Ct << " = " << Shoe[Ct].getRank() << Shoe[Ct].getSuit() << " value = " << Shoe[Ct].getVal() << endl; //just prints each Card. May be discarded later
            if(Ctr >= 52) Ctr = 0; //resets Ctr to 0 to get the next Deck of Cards
        }
    }while(Ct > 0);
}
//Check to see if anyone is busted
bool isBusted(int Total){
    if(Total > 21) return true;
    return false;
}
//Checks to see who wins
bool isWinner(int pTotal, int dTotal){
    if((pTotal >= dTotal && !(isBusted(pTotal))) || isBusted(dTotal)){
        if(pTotal == dTotal) cout << "It's a PUSH!!! ";
        return true;
    }
    else return false;
}
//Class Function definitions
//Card class functions
//default constructor for Card object
Card::Card(){
    //Initialize variables to zero or '0'
    c_Val = 0;
    c_Suit = '0';
    c_Rank = '0';
}
//sets the value of member variables to value of the parameters passed to the function
Card::Card(int val, char Suit, char Rank){
    c_Val = val;
    c_Suit = Suit;
    c_Rank = Rank;
}
//destructor for Card instance
Card::~Card(){
    //cleanup code here
}
//These functions return the value of each member variable
int Card::getVal(){ //returns the Card Value
    return c_Val;
}
char Card::getSuit(){ //returns the Card Suit
    return c_Suit;
}
char Card::getRank(){ //returns the Card Rank
    return c_Rank;
}
void Card::SetVal(int NewVal){ //Sets the Card Value to a New Value if needed
    c_Val = NewVal;
}
//Player class functions
//sets the Player Name and initializes variables to zero
Player::Player(string stName){
    Total = 0;
    p_Name = stName;
    DrawCt = 0; AceCt = 0;
}
//destructor for Player object
Player::~Player(){
    cout << "Goodbye, " << Name() << endl;
    //Cleanup code HERE, if needed
}
//Returns the Player Name
string Player::Name(){
    return p_Name;
}
//Outputs a greeting
void Player::Greet(){
    cout << "Hello, " << Name() << endl;
}
//Output the Player's Hole Cards
void Player::HoleCards(){
    cout << "Your cards:\n";
    cout << "[" << Hand[0].getRank() << " of " << Hand[0].getSuit() << "]|"
         << "[" << Hand[1].getRank() << " of " << Hand[1].getSuit() << "]\n";
}
//Draws a Card from the Shoe
void Player::DrawCard(Card Shoe[], int &Ct, int &t_Deck){
    if(t_Deck < 0){ //Checks for the end of the Shoe and reshuffles the Shoe
        cout << "End of shoe reached. Reshuffling now...\n";
        Shuffle(Shoe, Ct);
        t_Deck = Ct - 1;
    }
    if(DrawCt < 5 && t_Deck >= 0){ //Number of Cards drawn may NOT exceed 5
        Hand[DrawCt] = Shoe[t_Deck]; //Stores the Card drawn from the Shoe into the Hand array element Hand[Ct]
        ScoreIt(); //Score the Hand
        c_Card = Hand[DrawCt]; //Store the Card drawn as the Current Card;
        DrawCt++; //increment the number of Cards drawn
        t_Deck--; //decrement the Shoe counter for the next Card to be drawn
    }
    else{ //if maximum number of Cards Drawn per Hand is reached, Player is no longer allowed to draw any Cards
        cout << "You have drawn the maximum number of cards.\n";
        return;
    }
}
//Show the Card that was drawn
void Player::ShowCard(){
    cout << "Card drawn: [" << c_Card.getRank() << " of " << c_Card.getSuit() << "]\n" ;
}
//return the Players Total score
int Player::Totalup(){
    return Total;
}
//Determine the value of Player's Hand
void Player::ScoreIt(){
    bool Over = false; //boolean to check if Hand score is over 21
    int x;
    Total = 0;
    //Checks if the Current Total is Busted
    for(x = 0; x < 5; x++){
        if(Hand[x].getRank() == 'A') AceCt++; //increments Player's Ace Count for every Ace drawn
        c_Card = Hand[x]; //sets Current Card to the Card instance in Hand[x]
        Total += c_Card.getVal(); //get the value of the Current Card and add it to Total
    }
    Over = isBusted(Total); //if Total is Over 21, determine the Value of any Aces drawn
    Total = 0; //reset the Total to zero
    for(x = 0; x < 5; x++){
        while(AceCt > 0 && (Over)){
            Total -= 10; //if Total is Over 21, since value of Ace == 11, decrease Total by 10 to simulate a value of 1 for Ace
            AceCt--; //decrements Ace Count to account for each Ace in Player's Hand
            Over = isBusted(Total); //checks if Player is Over 21
        }
        c_Card = Hand[x]; //sets Current Card to the Card instance in Hand[x]
        Total += c_Card.getVal(); //get the value of the Current Card and add it to Total
    }
}
//Dealer functions
//sets the Dealers Name and initializes variables to zero
Dealer::Dealer(string stName):Player(stName){
    DrawCt = 0;
    AceCt = 0;
}
//destructor for Dealer
Dealer::~Dealer(){
    //cleanup code here
}
//Output the Dealer's Hole Cards
void Dealer::HoleCards(){
        cout << "[* of *]|" << "[" << Hand[1].getRank() << " of " << Hand[1].getSuit() << "]" << endl;
}
//Draws a Card from the Shoe
void Dealer::DrawCard(Card Shoe[], int &Ct, int &t_Deck){
    if(t_Deck < 0){ //Checks for the end of the Shoe and reshuffles the Shoe
        cout << "End of shoe reached. Reshuffling now...\n";
        Shuffle(Shoe, Ct);
        t_Deck = Ct - 1;
    }
    if(DrawCt < 5 && t_Deck >= 0){ //Number of Cards drawn may NOT exceed 5
        Hand[DrawCt] = Shoe[t_Deck]; //Stores the Card drawn from the Shoe into the Hand array element Hand[Ct]
        ScoreIt(); //Score the Hand
        c_Card = Hand[DrawCt]; //Store the Card drawn as the Current Card;
        DrawCt++; //increment the number of Cards drawn
        t_Deck--; //decrement the Shoe counter for the next Card to be drawn
    }
}
//Determine the value of Player's Hand
void Dealer::ScoreIt(){
    bool Over = false;
    int x;
    Total = 0;
    //Checks if the Current Total is Busted
    for(x = 0; x < 5; x++){
        if(Hand[x].getRank() == 'A') AceCt++; //increments Player's Ace Count for every Ace drawn
        c_Card = Hand[x]; //sets Current Card to the Card instance in Hand[x]
        Total += c_Card.getVal(); //get the value of the Current Card and add it to Total
    }
    Over = isBusted(Total); //if Total is Over 21, determine the Value of any Aces drawn
    Total = 0; //reset the Total to zero
    for(x = 0; x < 5; x++){
        while(AceCt > 0 && (Over)){
            Total -= 10; //if Total is Over 21, since value of Ace == 11, decrease Total by 10 to simulate a value of 1 for Ace
            AceCt--; //decrements Ace Count to account for each Ace in Player's Hand
            Over = isBusted(Total); //checks if Player is Over 21
        }
        c_Card = Hand[x]; //sets Current Card to the Card instance in Hand[x]
        Total += c_Card.getVal(); //get the value of the Current Card and add it to Total
    }
}