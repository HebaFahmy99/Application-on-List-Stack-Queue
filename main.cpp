
#include <iostream>
using namespace std;

class Rectangle
{
private: //private members of class rectangle
    int length;
    int width;
    int area;
public:
    Rectangle() //default constructor
    {
        length = 0; //intialization of length and width with zero
        width = 0;
        area = length * width;
    }

    Rectangle(int l, int w) //parametrized constructor that takes values from user
    {
        length = l;
        width = w;
        area = l * w;
    }
    int getLength() //function to get length
    {
        return length;
    }
    int getWidth() //function to get width
    {
        return width;
    }
    int getArea() //function to get area
    {
        return length * width;
    }
    friend ostream& operator<<(ostream& output, const Rectangle& rect)
    {
        //operator overloading function to print
        output << "Length=" << rect.length <<",Width="<< rect.width << ",Area=" << rect.area << endl;
    }
};

template <class elems> //class mylist and make it template to be of different data types
class MyList{
protected:
    int itsSize;
    elems* arrayOfElements; //array of data type elems
public:
    MyList(int s)
    {
        itsSize = s;
        arrayOfElements = new elems[s]; //dynamic array of elems data type with the size that will be entered by user
    }
    virtual~MyList()
    { //destructor to delete the array
            delete[] arrayOfElements;
    }
    int getSize() //function to get the size
    {
        return itsSize;
    }
    //pure virtual functions //it make the class abstract //No implmentation
    virtual void addElem(elems)=0 ;
    virtual elems getElem()=0;
    virtual bool isEmpty()=0;
    virtual bool isFull()=0;
    virtual void clearItems()=0;

};

template <class elems>
class MyStack : public MyList<elems> {  //class mystack inherited from class mylist
 private:
     //attributes inherited from template class my list
    MyList<elems>::itsSize;
    MyList<elems>::arrayOfElements;
    int top;
public:
   MyStack(int s) : MyList<elems>(s) //parametrized constructor
    {
        top= -1 ;
    }

    bool isEmpty()
    {
        if (top == -1) //no elements stored
            return true;
        else
            return false;
    }
    void addElem(elems element)
    {
        if (isFull()) //to check if the array is empty or not
        {
            cout << "Stack is full\n";
        }
        else
        {
            top++; //increment top by one , -1+1 = 0
            arrayOfElements[top] = element ; //store the element at index zero then increment top and repeat
        }
    }
    elems getElem()
    {
        if(isEmpty())
        {
            cout << "Stack is Empty\n";
        }
        else
        { //else then the stack is full
            top -- ; //decrement the top by one
            for (int i=top ; i>=0 ; i-- )
            {
              return arrayOfElements[i] ;
            }
        }
    }
    void DisplayAllElements() //function to display all elements stored in the array with the correct order
    {
        cout << "All Elements" << endl;
        for (int i=top ; i>=0 ; i-- )
        { //the counter start with top where the last element is stored then start printing
            cout << "Element--> " <<arrayOfElements[i] << endl;
        }
    }
  bool isFull()
    {
        if (top == itsSize -1) //if top is the last element stored then it means that stack is full
            return true;
        else
            return false;
    }
    void clearItems()
    {
        delete [] arrayOfElements; // free current memory occupied by the stack
        top=-1; // reset top
        arrayOfElements = new elems[itsSize] ; // assign new memory
    }
};
template <class elems>
class MyQueue : public MyList<elems> { //class myqueue inherited from mylist class
private:
    //attributes inherited from template class my list
    MyList<elems>::itsSize ;
    MyList<elems>::arrayOfElements;
    int first , last ; //define two attributes
public:
    MyQueue(int s) : MyList<elems>(s) //parameterized constructor
    {

        first = -1 ; //to detect place of first element stored
        last = -1 ; //to detect place of last element stored
    }
    void addElem(elems item)
    {
        if(last != itsSize -1) //if the last cell is empty
        {
            if ((first == -1) && (last == -1)) //to check if there is no element stored in the array
            {
                last ++ ; //if yes shift last to next position
                first++; //if yes shift first to next position
                arrayOfElements[last] = item ; //add element
            }
            else
            { //add element to the stored elements before
                last++ ;
                arrayOfElements[last] = item ;
            }
        }
        else{
            cout << "Queue is full" ;
        }
    }
    elems getElem()
    {
        if ((first != -1) && (last!= -1)) //not empty
        {
            first++ ;
            return arrayOfElements[first] ; //return the element stored
        }
        else
        {
            cout << "Queue is empty\n" ;
        }
    }
    bool isFull()
    {
        if(last = itsSize-1)
            return true ;
        else
            return false ;
    }
    bool isEmpty()
    {
        if((first==-1 && last == -1) || (last!= itsSize -1)) //if it is totally empty
            //or it already has elements and not full
            return true ;
        else
            return false ;
    }
    void DisplayAllElements() //functions to display all elements stored in the array
    {
        cout << "All Elements" << endl;
        for (int i=first ; i<= last ; i++)
            cout << "Element--> " << arrayOfElements[i] << endl;
    }
    void clearItems()
    {
        delete [] arrayOfElements ; //free memory on the heap
        first = -1 ; //reset
        last = -1 ; //reset
        arrayOfElements = new elems[itsSize] ;  //construct new array
    }
};


int main()
{
    char answer ;
    cout << "Would you like to use a stack or a queue(S/Q)?\n";
    cin >> answer;
    int numberOfItems;
    try {
    cout << "How many items to be stored?\n";
    cin >> numberOfItems;
    if (numberOfItems<=0) //an exception to be handled if the user entered negative or zero size
        throw 0;
        }

    catch(int &numberOfItemsNotValid)
    {
        cout << "Number of items is not valid, Try again" << endl ;
        cout << "How many items to be stored?\n"; //new chance
        cin >> numberOfItems;
    }
    if ((answer == 's') || (answer == 'S'))
    {
        int whichType ; //choose to use stack
        cout << "would you like to store integers, strings, or rectangles(1,2 or 3)?\n";
        cin >> whichType ;
        if (whichType == 1)
        { //integer option
            MyStack<int>stackObj(numberOfItems); //create an object of integer data type
            int intChoice;

            for (int i = 0; i < stackObj.getSize(); i++) //loop is controlled by the size of the array
            {
                try {
                cout << "Enter num:";
                cin >> intChoice;

                if (!cin) //string exception //if the entered data type is not the same data type declared
                    throw " Error ";
                if(intChoice <=0)
                   throw 0; //second exception to handle negative or zero numbers

                stackObj.addElem(intChoice);
                     }

                catch (const char *StringException)
                { // "Integer choice but string input(Invalid)\n";
               stackObj.addElem(0);
               cout << "wrong string Input-->will enter 0" << endl ;

                }
                catch(int &zeroException)
                {
                 cout << "You have entered a negative or zero number\n";
                }
            }
            cout << endl;
            stackObj.DisplayAllElements();
        }
        else if(whichType == 2)
        {
            //string choice
            MyStack<string>stackObj(numberOfItems); //create an object of string data type
            string stringChoice ;
            for (int i = 0; i < stackObj.getSize(); i++)
            {
                cout << "Enter string:";
                cin >> stringChoice;
                stackObj.addElem(stringChoice);
            }
            cout << endl ;
            stackObj.DisplayAllElements();
        }
        else if (whichType == 3)
        {
            //rectangle choice
            int length , width ;
            MyStack<Rectangle>stackObj(numberOfItems); //create an object of rectangle class data type

            for (int i = 0; i < stackObj.getSize(); i++)
            {
                try {
                    cout << "Enter length and width space separated:";
                    cin >> length >> width;
                    if(length<0 || width<0) //third exception to handle negative length or width
                        throw 0;
                    Rectangle rectangleObj(length,width); //create object of class rectangle
                    stackObj.addElem(rectangleObj) ; //add rectangle in the array
                    }
                    catch (int &InvalidParameters)
                    {
                        cout << "Wrong length or width entering 0 and 0" << endl ;
                        Rectangle rectangleObj(0,0); //make length and width zero
                        stackObj.addElem(rectangleObj) ; //add rectangle with zero length and zero width
                    }
            }
            cout << endl ;
            stackObj.DisplayAllElements();
        }
        else
        {
            cout << "Invalid choice\n";
        }
    }
    else if((answer == 'Q') || (answer == 'q'))
    { //choose to store elements in queue
        int whichType ;
        cout << "would you like to store integers, strings, or rectangles(1,2 or 3)?\n";
        cin >> whichType ;
        if (whichType == 1)
        {
             MyQueue<int>queueObj(numberOfItems);
            int intChoice;
            for (int i = 0; i < queueObj.getSize(); i++)
            {
                try {
                    cout << "Enter num:";
                    cin >> intChoice;
                    if(intChoice <=0)
                        throw 0;
                    queueObj.addElem(intChoice);
                        }
                catch(int &zeroException)
                    {
                    cout << "You have entered a negative or zero number\n";
                    }
            }
            cout << endl ;
            queueObj.DisplayAllElements();
        }
        else if(whichType == 2)
        {
            MyQueue<string>queueObj(numberOfItems);
            string stringChoice ;
            for (int i = 0; i < queueObj.getSize(); i++)
            {
                cout << "Enter string:";
                cin >> stringChoice;
                queueObj.addElem(stringChoice);
            }
            cout << endl ;
            queueObj.DisplayAllElements();
        }
        else if (whichType == 3)
        {
            int length , width ;
            MyQueue<Rectangle>queueObj(numberOfItems);

            for (int i = 0; i < queueObj.getSize(); i++)
            {
                try {
                    cout << "Enter length and width space separated:";
                    cin >> length >> width;
                    if(length<0 || width<0)
                        throw 0;
                    Rectangle rectangleObj(length,width);
                    queueObj.addElem(rectangleObj) ;
                    }
                    catch (int &InvalidParameters)
                    {
                        cout << "Wrong length or width entering 0 and 0" << endl ;
                        Rectangle rectangleObj(0,0);
                        queueObj.addElem(rectangleObj) ;
                    }
            }
            cout << endl ;
            queueObj.DisplayAllElements();
        }
    }
    else
        cout << "Invalid choice\n";
}


