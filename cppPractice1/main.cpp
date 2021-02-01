#include <cstdio>
#include <cstdint>

/*
 Initializing fundamental types to zero
 
 int a = 0;    ➊// Initialized to 0
 int b{};      ➋// Initialized to 0
 int c = {};   ➌// Initialized to 0
 int d;        ➍// Initialized to 0 (maybe)
 
 2 and 3 is called braced initialization
 number 4 is unreliable so don't use it
 
 
 Intializing fundamental types to arbitrary value
 
 int e = 42;    ➊ // Initialized to 42
 int f{ 42 };   ➋ // Initialized to 42
 int g = { 42 };➌ // Initialized to 42
 int h(42);     ➍ // Initialized to 42
 
 
 */

//scoped enum
enum class HogwardsHouses {
    Godric_Gryffindor,
    Salazar_Slytherin,
    Rowena_Ravenclaw,
    Helga_Hufflepuff
};

//POD Plain Old Data Classes
//Generally order the members from largest to smallest
struct Book {
    char name[256];
    int year;
    int pages;
    bool hardCover;
};

//union
//data is stored in the same memory location
//you can only use only on of the mambers
//like if you use the string then you cannot use the integer part else there will be data corruption
//you can change the member you want to use though
//but you cannot reuse the old type
//size of union is the size of the largest member in this case it is probably string
union Variant {
  char string[10];
  int integer;
  double floating_point;
};

//classes
//keyword class declares members private by deafault
//you can also use the keyword struct which declare its members pubic by default
class ClockOfTheLongNow {
    int year;
    
public:
    //constructors
    //don't state a reutrn type
    //when you create a ClockOfTheLongNow class the constructor is called
    //and this case the year is set to 2019 by default
    //constructors can take as many parameters though
    ClockOfTheLongNow(int year_in) {
        //if set_year fails it will set the default year to 2019
        if(!set_year(year_in)) {
            year = 2019;
        }
    }
    
    void add_year() {
        year++;
    }
    
    //setter
    bool set_year(int year) {
        if(year < 2019) {
            return false;
        }
        this->year = year;
        return true;
        
    }
    
    //getter
    //const methods are read-only methods
    //the method does not change the current objects state within the const method
    int get_year() const{
        return year;
    }
};

//using refences
void add_year(ClockOfTheLongNow &clock) {
    clock.set_year(clock.get_year() + 1); // No deref operator needed
}

//if get_year is not const the program will not compile as clock is a const reference and cannot be modified within is_leap_year
bool is_leap_year(const ClockOfTheLongNow& clock) {
  if (clock.get_year() % 4 > 0) return false;
  if (clock.get_year() % 100 > 0) return true;
  if (clock.get_year() % 400 > 0) return false;
  return true;
}

//member initiazer lists
//must be same order as the declaration
/*
 Advantages of member intializer lists
 - It ensures validity of all members before the constructor executes, so you can focus on initialization logic rather than member error checking.
 - The members initialize once. If you reassign members in the constructor, you potentially do extra work.
 */

struct Avout {
    Avout(const char *name, int year_of_apert)
        : name{ name }, apert{ year_of_apert } {
    }
    
    void announce() const {
        printf("My name is %s and my next apert is %d.\n", name, apert.get_year());
    }
    const char* name = "Erasmas";
    ClockOfTheLongNow apert;
};

struct PodStruct {
    u_int64_t a;
    char b[256];
    bool c;
};

//fully featured classes are always initialized when an object is created
//hence one of the constructors will be called depending on the arguements during initialization
struct Taxonomist {
  Taxonomist() {
    printf("(no argument)\n");
  }
  Taxonomist(char x) {
    printf("char: %c\n", x);
  }
  Taxonomist(int x) {
    printf("int: %d\n", x);
  }
  Taxonomist(float x) {
    printf("float: %f\n", x);
  }
};

//you can use braced initialization to initialized members of classses
//braced initialization aka uniform initialization
struct JohanVanDerSmut {
    bool gold = true;
    int year_of_smelting_accident{ 1970 };
    char key_location[8] = { "x-rated" };
};

struct Earth {
    ~Earth() { // Earth's destructor
        printf("Making way for hyperspace bypass");
    }
};

struct College {
    char name[256];
};

//linked list
struct Element {
  Element* next{};
  void insert_after(Element* new_element) {
    new_element->next = this->next;
    this->next = new_element;
  }
  char prefix[2];
  short operating_number;
};

void printName(College *college_ptr) {
    printf("%s College\n", college_ptr->name);
}

//pointer-plus-size approach to passing arrays
void printNames(College *college_ptr, size_t n_college) {
    for(size_t i = 0; i < n_college; i++) {
        printf("%s College\n", (*(college_ptr+i)).name);
        //since array acts like a pointer we can use the dot operator?
        printf("%s College\n", college_ptr[i].name);
    }
}

int aboslute_value(int inputNum) {
    
    if(inputNum >= 0) {
        return inputNum;
    } else {
        return inputNum*-1;
    }
}

int sum(int num1, int num2) {
    return num1 + num2;
}

void printAlphabets() {
    
    //do lower case letter first
    char alphabets[27];
    //last element in char array is 0
    alphabets[26] = 0;
    
    for(size_t i = 0; i < 26; i++) {
        alphabets[i] = i + 97;
    }
    
    printf("upper case alphabets: %s\n", alphabets);
    
    //then change it into upper case
    for(size_t i = 0; i < 26; i++) {
        alphabets[i] = i + 65;
    }
    
    printf("upper case alphabets: %s\n", alphabets);
}

void petruchio(const char* shrew) {
  printf("Fear not, sweet wench, they shall not touch thee, %s.\n", shrew);
  //shrew[0] = "K";  // Compiler error! The shrew cannot be tamed.
}

//static means its lifetime is the program's lifetime
//declare at global means all functions in the translation unit can access it
static int rat_things_power = 200;
//can use extern keyword
//extern external linkage means variable is accessible to other translation units
//intern for internal linkage

void power_up_rat_thing(int nuclear_isotopes) {
    rat_things_power = rat_things_power + nuclear_isotopes;
    const auto waste_heat = rat_things_power * 20;
    if (waste_heat > 10000) {
        printf("Warning! Hot doggie!\n");
    }
}


int main() {
    
    int my_num = 9;
    int my_num2 = 8;
    int array[4] = {1,2,9,4};
    
    printf("absolute value of %d is %d\n", my_num, aboslute_value(my_num));
    printf("The sum of %d + %d = %d\n", my_num, my_num2, sum(my_num, my_num2));
    
    int maximum = array[0];
    //range-based for loop
    for(int i: array) {
        if(i > maximum) {
            maximum = i;
        }
    }
    
    printf("The maximum value in the array is %d\n", maximum);
    
    printAlphabets();
    
    HogwardsHouses harryPotter_HogwardsHouse = HogwardsHouses::Godric_Gryffindor;
    
    switch(harryPotter_HogwardsHouse) {
        case HogwardsHouses::Godric_Gryffindor: {
            printf("Godric Gryffindor\n");
        } break;
        case HogwardsHouses::Salazar_Slytherin: {
            printf("Salazar Slytherin\n");
        } break;
        case HogwardsHouses::Rowena_Ravenclaw: {
            printf("Rowena Ravenclaw\n");
        } break;
        case HogwardsHouses::Helga_Hufflepuff: {
            printf("Helga Hufflepuff\n");
        } break;
        default: {
            printf("You must be a muggle\n");
        }
    }
    
    struct Book harryPotter;
    harryPotter.pages = 256;
    
    printf("Harry potter has %d pages\n", harryPotter.pages);
    
    Variant v;
    v.integer = 42;
    printf("The ultimate answer: %d\n", v.integer);
    v.floating_point = 2.7182818284;
    printf("Euler's number e:    %f\n", v.floating_point);
    //you can't access the old data as only one member may be used at a time
    printf("A dumpster fire:     %d\n", v.integer);
    
    ClockOfTheLongNow clock(2021);
    printf("Initial default year: %d\n", clock.get_year());
    if(!clock.set_year(2018)) {
        //2018 will fail due to the method
        clock.set_year(2019);
    }
    clock.add_year();
    printf("year: %d\n", clock.get_year());
    
    PodStruct initialized_pod1{}; //All fields zeroed
    PodStruct initialized_pod2 = {}; //All fields zeroed
    
    PodStruct initialized_pod3{42, "Hello"}; // Fields a & b set; c = 0;
    PodStruct initialized_pod4 = {42, "Hello", true}; // All fields set
    
    printf("initialized_pod1.b %s\n", initialized_pod1.b);
    //string set to 0 means null string
    
    //Array initialization
    
    int array_1[]{ 1, 2, 3 }; // Array of length 3; 1, 2, 3
    int array_2[5]{}; // Array of length 5; 0, 0, 0, 0, 0
    int array_3[5]{ 1, 2, 3 }; // Array of length 5; 1, 2, 3, 0, 0
    int array_4[5]; // Array of length 5; uninitialized values
    
    Taxonomist t1;
    Taxonomist t2{ 'c' };
    Taxonomist t3{ 65537 };
    Taxonomist t4{ 6.02e23f };
    Taxonomist t5('g');
    Taxonomist t6 = { 'l' };
    Taxonomist t7{};
    //Taxonomist t8(); is a function declaration
    
    
    int gettysburg{};
    printf("gettysburg: %d\n", gettysburg);
    int *gettysburg_address = &gettysburg;
    printf("&gettysburg: %p\n", gettysburg_address);
    *gettysburg_address = 17325;
    printf("*gettysburg_address: %d\n", *gettysburg_address);
    printf("gettysburg: %d\n", gettysburg);
    printf("gettysburg_ddress: %p\n", gettysburg_address);
    
    ClockOfTheLongNow *clock_ptr = &clock;
    clock_ptr->set_year(2020);
    printf("Address of clock %p\n", clock_ptr);
    // -> pointer to member operator
    printf("Value of clock's year: %d\n", clock_ptr->get_year());
    printf("Value of clock's year: %d\n", (*clock_ptr).get_year());
    
    int key_to_the_universe[]{3, 6, 9};
    //array may decay into pointer
    int *key_ptr = key_to_the_universe; // points to 3
    
    College best_colleges[] = {"Magdalen", "Nuffield", "Kellogg"};
    printName(best_colleges);
    printNames(best_colleges, sizeof(best_colleges)/sizeof(College));
    
    //pointer arithmetic
    College *third_college_ptr = &best_colleges[2];
    printf("Third college ptr: %s\n", third_college_ptr->name);
    third_college_ptr = best_colleges + 2;
    printf("Third college ptr: %s\n", third_college_ptr->name);
    
    char lower[] = "abc?e";
    char upper[] = "ABC?E";
    char* upper_ptr = upper;      // Equivalent: &upper[0]

    lower[3] = 'd';               // lower now contains a b c d e \0
    upper_ptr[3] = 'D';             // upper now contains A B C D E \0

    char letter_d = lower[3];     // letter_d equals 'd'
    char letter_D = upper_ptr[3];   // letter_D equals 'D'

    printf("lower: %s\nupper: %s\n", lower, upper);

    //lower[7] = 'g';               // Super bad. You must never do this.
    
    //now using pointer arithmethic
    *(lower + 3) = 'd';
    *(upper_ptr + 3) = 'D';

    letter_d = *(lower + 3); // lower decays into a pointer when we add
    letter_D = *(upper_ptr + 3);

    printf("lower: %s\nupper: %s\n", lower, upper);
    
    /*
     
     Pointers have an implicit conversion to bool. Any value that is not nullptr converts implicitly to true, whereas nullptr converts implicitly to false. This is useful when a function returning a pointer ran successfully. A common idiom is that such a function returns nullptr in the case of failure. The canonical example is memory allocation.
     
     */
    
    printf("The year is %d\n", clock.get_year());
    add_year(clock); // clock is implicitly passed by reference
    printf("The year is %d\n", clock.get_year());
    
    //linked list of stormtroopers
    Element trooper1, trooper2, trooper3;
    trooper1.prefix[0] = 'T';
    trooper1.prefix[1] = 'K';
    trooper1.operating_number = 421;
    trooper1.insert_after(&trooper2);
    trooper2.prefix[0] = 'F';
    trooper2.prefix[1] = 'N';
    trooper2.operating_number = 2187;
    trooper2.insert_after(&trooper3);
    trooper3.prefix[0] = 'L';
    trooper3.prefix[1] = 'S';
    trooper3.operating_number = 005;

    for (Element *cursor = &trooper1; cursor; cursor = cursor->next) {
        printf("stormtrooper %c%c-%d\n",
               cursor->prefix[0],
               cursor->prefix[1],
               cursor->operating_number);
    }
    
    //references cannot be reseated
    //but pointers can
    //like pointer can point to a different memory address
    //reference cannot
    //if you change it you will just change the value of the original reference
    //as it will always refer to the original
    int original = 100;
    int& original_ref = original;
    printf("Original:  %d\n", original);
    printf("Reference: %d\n", original_ref);

    int new_value = 200;
    original_ref = new_value;
    printf("Original:  %d\n", original);
    printf("New Value: %d\n", new_value);
    printf("Reference: %d\n", original_ref);
    
    petruchio("shrew");
    
    Avout raz{ "Erasmas", 3010 };
    Avout jad{ "Jad", 4000 };
    raz.announce();
    jad.announce();
    
    //auto
    auto the_answer { 42 };            // int
    auto foot { 12L };                 // long
    auto rootbeer { 5.0F };            // float
    auto cheeseburger { 10.0 };        // double
    auto politifact_claims { false };  // bool
    auto cheese { "string" };          // char[7]
    
    //auto and reference types
    auto year { 2019 };              // int
    auto& year_ref = year;           // int&
    const auto& year_cref = year;    // const int&
    auto* year_ptr = &year;          // int*
    const auto* year_cptr = &year;   // const int*
    
    
    /*
     struct Dwarf {
       --snip--
     };

     Dwarf dwarves[13];

     struct Contract {
       void add(const Dwarf&);
     };

     void form_company(Contract &contract) {
       for (const auto& dwarf : dwarves) { ➊
         contract.add(dwarf);
       }
     }
     */
    
    
    printf("Rat-thing power: %d\n", rat_things_power);
    power_up_rat_thing(100);
    printf("Rat-thing power: %d\n", rat_things_power);
    power_up_rat_thing(500);
    printf("Rat-thing power: %d\n", rat_things_power);
    
    return 0;
}
