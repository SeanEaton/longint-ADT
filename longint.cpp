/*
A program for an abstract representation of a long integer via implementing a double ended linked queue of nodes with character variables.
*/
#include "longint.h"

/*
*----------------------------- I/O OPERATORS ---------------------------------
*/
//------------------------- operator>> overload ------------------------------
//populate a LongInt via input
//precondition: a LongInt fed a string via input operator
//postcondition: the LongInt will be populated via the string inputted
istream& operator>>(istream& input, LongInt& li){
    string str;
    input >> str;
    li.negative = false;
    int i = 0;
    li.digits.clear();
    for (char c : str) {
        if (c == '-' && i == 0) {
            li.negative = true;
        }
        else if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' 
        || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') {
            li.digits.addBack(c);
        }
        i++;
    }
    if (li.negative == true && !li.digits.isEmpty()) li.digits.addFront('-');
    li.remove0s();
    return input;
}

//------------------------- operator<< overload ------------------------------
//print out a LongInt in integer form
//precondition: a LongInt
//postcondition: that LongInt will have been printed to output
ostream& operator<<(ostream& output, const LongInt& rhs) {
    Deque<char> temp = rhs.digits;
    while (!temp.isEmpty()) {
        output << temp.removeFront();
    }
    temp.~Deque();
    return output;
}

/*
*------------------------ CONSTRUCTORS/DESTRUCTORS ----------------------------
*/
//------------------------------- default -------------------------------------
//creates a LongInt
//precondition: none
//postcondition: an empty LongInt (0)
LongInt::LongInt() {
    negative = false;
    digits.addBack('0');
}

//--------------------------- copy constructor --------------------------------
//creates a LongInt identical to the parameter
//precondition: another LongInt as parameter
//postcondition: an identical copy of the LongInt parameter
LongInt::LongInt(const LongInt &rhs) {
    digits.clear();
    digits = rhs.digits;
    negative = rhs.negative;
}

//------------------------ constructor via string -----------------------------
//creates a LongInt from string parameter
//precondition: a string parameter
//postcondition: a LongInt parsed from string parameter
LongInt::LongInt(const string str) {
    negative = false;
    int i = 0;
    for (char c : str) {
        if (c == '-' && i == 0) {
            negative = true;
        }
        else if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' 
        || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') {
            digits.addBack(c);
        }
        i++;
    }
    if (negative == true && !digits.isEmpty()) digits.addFront('-');
    remove0s();
}

//------------------------------ destructor -----------------------------------
//deallocates a LongInt from system memory
//precondition: a LongInt
//postcondition: this LongInt (and the Deque within) will be deallocated from system memory
LongInt::~LongInt() {
    digits.~Deque();
}

/*
*--------------------------- ARITHMETIC OPERATORS -----------------------------
*/
//-------------------------------- addition -----------------------------------
//adds two LongInts together
//precondition: two LongInts as operands
//postconditions: return the sum of the LongInt operands
LongInt LongInt::operator+(const LongInt &rhs) const {
    LongInt temp1 = *this;
    LongInt temp2 = rhs;
    if (!temp1.negative && temp2.negative) {
        temp2.negative = false;
        temp2.digits.removeFront(); 
        return temp1 - temp2;
    }
    if (temp1.negative && !temp2.negative) {
        temp1.negative = false;
        temp1.digits.removeFront(); 
        return temp2 - temp1;
    }
    LongInt sum;
    sum.digits.clear();
    int ans = 0;
    int carry = 0;
    int t1 = 0;
    int t2 = 0;
    if (temp1.negative) {
        temp1.digits.removeFront();
        temp2.digits.removeFront();
    }
    while (!temp1.digits.isEmpty() || !temp2.digits.isEmpty() || carry > 0) {
        t1 = 0;
        t2 = 0;
        if (!temp1.digits.isEmpty() && !temp2.digits.isEmpty()){
            t1 = temp1.digits.removeBack() - '0';
            t2 = temp2.digits.removeBack() - '0';
        }
        else if (temp1.digits.isEmpty() && temp2.digits.isEmpty());
        else if (temp1.digits.isEmpty()) {
            t2 = temp2.digits.removeBack() - '0';
        }
        else if (temp2.digits.isEmpty()) {
            t1 = temp1.digits.removeBack() - '0';
        }
        ans = (t1 + t2 + carry) % 10;
        carry = (t1 + t2 + carry) / 10;
        sum.digits.addFront('0' + ans);
    }
    if (temp1.negative) {
        sum.negative = true;
        sum.digits.addFront('-');
    }
    temp1.~LongInt();
    temp2.~LongInt();
    return sum;
}

//------------------------------ subtraction ----------------------------------
//subtracts one LongInt from another
//precondition: two LongInts as operands
//postconditions: return the difference of the LongInt operands, subtracting right from left
LongInt LongInt::operator-(const LongInt &rhs) const {
    LongInt temp1 = *this;
    LongInt temp2 = rhs;
    if (!temp1.negative && temp2.negative) {
        temp2.negative = false;
        temp2.digits.removeFront(); 
        return temp1 + temp2;
    }
    if (temp1.negative && !temp2.negative) { 
        temp2.negative = true;
        temp2.digits.addFront('-');
        return temp1 + temp2;
    }
    if (temp1.negative && temp2.negative) { 
        temp1 = rhs;
        temp2 = *this;
        temp1.digits.removeFront();
        temp2.digits.removeFront();
        temp1.negative = false;
        temp2.negative = false;
    }
    LongInt dif;
    dif.digits.clear();
    int t1 = 0;
    int t2 = 0;
    if (temp2 > temp1) {
        LongInt temp3 = temp2;
        temp2 = temp1;
        temp1 = temp3;
        temp3.~LongInt();
        dif.negative = true;
    }
    while (!temp1.digits.isEmpty()) {
        t1 = temp1.digits.removeBack() - '0';
        t2 = 0;
        if (!temp2.digits.isEmpty()) {
            t2 = temp2.digits.removeBack() - '0';
        }
        if (t2 > t1) {
            temp1.borrow();
            t1 += 10;
        }
        dif.digits.addFront('0' + (t1 - t2));
    }
    temp1.~LongInt();
    temp2.~LongInt();
    if (dif.negative == true) dif.digits.addFront('-');
    dif.remove0s();
    return dif;
}

/*
*--------------------------- ASSIGNMENT OPERATORS -----------------------------
*/
//--------------------------- simple assignment -------------------------------
//assigns left LongInt to right LongInt
//precondition: two LongInts as operands
//postconditions: left operand will be identical to right operand
const LongInt& LongInt::operator=(const LongInt &rhs) {
    digits.clear();
    digits = rhs.digits;
    negative = rhs.negative;
    return *this;
}

/*
--------------------------- COMPARISON OPERATORS ------------------------------
*/
//------------------------------- less than -----------------------------------
//checks if the left hand LongInt is less than the right hand LongInt
//precondition: two LongInts as operands
//postconditions: returns true if left is less, returns false if not
bool LongInt::operator<(const LongInt &rhs) const { // this < rhs
    if (negative != rhs.negative) {
        if (negative == true) return true;
        return false;
    }
    if (digits.size() != rhs.digits.size()) {
        if (negative == false && digits.size() < rhs.digits.size()) return true;
        if (negative == true && digits.size() > rhs.digits.size()) return true;
        return false;
    }
    Deque<char> temp1 = digits;
    Deque<char> temp2 = rhs.digits;
    if (negative) {
        temp1.removeFront();
        temp2.removeFront();
    }
    while (!temp1.isEmpty()) {
        int c1 = temp1.removeFront() - '0';
        int c2 = temp2.removeFront() - '0';
        if (c1 != c2) {
            if (negative && c1 < c2) return false;
            if (!negative && c1 > c2) return false;
            return true;
        }
    }
    temp1.~Deque();
    temp2.~Deque();
    return false;
}

//-------------------------- less than or equal to ----------------------------
//checks if the left hand LongInt is less than or equal to the right hand LongInt
//precondition: two LongInts as operands
//postconditions: returns true if left is less or equal, returns false if not
bool LongInt::operator<=(const LongInt &rhs) const {
    if (negative != rhs.negative) {
        if (negative == true) return true;
        return false;
    }
    if (digits.size() != rhs.digits.size()) {
        if (negative == false && digits.size() < rhs.digits.size()) return true;
        if (negative == true && digits.size() > rhs.digits.size()) return true;
        return false;
    }
    Deque<char> temp1 = digits;
    Deque<char> temp2 = rhs.digits;
    if (negative) {
        temp1.removeFront();
        temp2.removeFront();
    }
    while (!temp1.isEmpty()) {
        int c1 = temp1.removeFront() - '0';
        int c2 = temp2.removeFront() - '0';
        if (c1 != c2) {
            if (negative && c1 < c2) return false;
            if (!negative && c1 > c2) return false;
            return true;
        }
    }
    temp1.~Deque();
    temp2.~Deque();
    return true;
}

//------------------------------ greater than ---------------------------------
//checks if the left hand LongInt is greater than the right hand LongInt
//precondition: two LongInts as operands
//postconditions: returns true if left is greater, returns false if not
bool LongInt::operator> (const LongInt &rhs) const {
    if (negative != rhs.negative) {
        if (negative == true) return false;
        return true;
    }
    if (digits.size() != rhs.digits.size()) {
        if (negative == false && digits.size() < rhs.digits.size()) return false;
        if (negative == true && digits.size() > rhs.digits.size()) return false;
        return true;
    }
    Deque<char> temp1 = digits;
    Deque<char> temp2 = rhs.digits;
    if (negative) {
        temp1.removeFront();
        temp2.removeFront();
    }
    while (!temp1.isEmpty()) {
        int c1 = temp1.removeFront() - '0';
        int c2 = temp2.removeFront() - '0';
        if (c1 != c2) {
            if (negative && c1 < c2) return true;
            if (!negative && c1 > c2) return true;
            return false;
        }
    }
    temp1.~Deque();
    temp2.~Deque();
    return false;
}

//------------------------ greater than or equal to ---------------------------
//checks if the left hand LongInt is greater than or equal to the right hand LongInt
//precondition: two LongInts as operands
//postconditions: returns true if left is greater or equal, returns false if not
bool LongInt::operator>=(const LongInt &rhs) const {
    if (negative != rhs.negative) {
        if (negative == true) return false;
        return true;
    }
    if (digits.size() != rhs.digits.size()) {
        if (negative == false && digits.size() < rhs.digits.size()) return false;
        if (negative == true && digits.size() > rhs.digits.size()) return false;
        return true;
    }
    Deque<char> temp1 = digits;
    Deque<char> temp2 = rhs.digits;
    if (negative) {
        temp1.removeFront();
        temp2.removeFront();
    }
    while (!temp1.isEmpty()) {
        int c1 = temp1.removeFront() - '0';
        int c2 = temp2.removeFront() - '0';
        if (c1 != c2) {
            if (negative && c1 < c2) return true;
            if (!negative && c1 > c2) return true;
            return false;
        }
    }
    temp1.~Deque();
    temp2.~Deque();
    return true;
}

//-------------------------------- equal to -----------------------------------
//checks whether two LongInts are identical
//precondition: two LongInts as operands
//postconditions: returns true if operands are identical, returns false if they are not
bool LongInt::operator==(const LongInt &rhs) const {
    if (negative != rhs.negative) return false;
    if (digits.size() != rhs.digits.size()) return false;
    Deque<char> temp1 = digits;
    Deque<char> temp2 = rhs.digits;
    if (negative) {
        temp1.removeFront();
        temp2.removeFront();
    }
    while (!temp1.isEmpty()) {
        int c1 = temp1.removeFront() - '0';
        int c2 = temp2.removeFront() - '0';
        if (c1 != c2) {
            return false;
        }
    }
    temp1.~Deque();
    temp2.~Deque();
    return true;
}

//------------------------------ not equal to ---------------------------------
//checks whether two LongInts are not identical
//precondition: two LongInts as operands
//postconditions: returns true if operands are not identical, returns false if they are
bool LongInt::operator!=(const LongInt &rhs) const { 
    if (negative != rhs.negative) return true;
    if (digits.size() != rhs.digits.size()) return true;
    Deque<char> temp1 = digits;
    Deque<char> temp2 = rhs.digits;
    if (negative) {
        temp1.removeFront();
        temp2.removeFront();
    }
    while (!temp1.isEmpty()) {
        int c1 = temp1.removeFront() - '0';
        int c2 = temp2.removeFront() - '0';
        if (c1 != c2) {
            return true;
        }
    }
    temp1.~Deque();
    temp2.~Deque();
    return false;
}

/*
*--------------------------- MUTATORS/ACCESSORS -------------------------------
*/
//------------------------------ remove0s -------------------------------------
//removes inaccurate zero's from this LongInt
//precondition: a LongInt
//postconditions: a LongInt without inaccurate zeros (an accurate integer representation)
void LongInt::remove0s() {
    if (digits.isEmpty()) {
        digits.addFront('0');
        return;
    }
    char c;
    if (negative) digits.removeFront();
    c = digits.getFront();
    while (c == '0' && !digits.isEmpty()) {
        digits.removeFront();
        if (!digits.isEmpty()) c = digits.getFront();
    }
    if (digits.isEmpty()) digits.addFront('0');
    else if (negative) digits.addFront('-');
}

//------------------------------- borrow --------------------------------------
//alters this LongInt to reflect a borrow operation performed in subtraction
//precondition: a LongInt
//postconditions: a LongInt having undergone a borrow operation
void LongInt::borrow() {
    LongInt temp;
    temp.digits.clear();
    while (!digits.isEmpty() && digits.getBack() == '0') {
        digits.removeBack();
        temp.digits.addFront('9');
    }
    if (!digits.isEmpty() && digits.getBack() != '0') {
        int borrowee = (digits.removeBack() - '0') - 1;
        temp.digits.addFront('0' + borrowee);
    }
    while (!digits.isEmpty()) {
        temp.digits.addFront(digits.removeBack());
    }
    temp.remove0s();
    *this = temp;
    temp.~LongInt();
}


