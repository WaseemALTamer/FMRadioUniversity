



typedef void (*ApplyFunc)(const char* newValue);

struct Page {
    char title[16];   // e.g. "Time", "Volume", "Frequency" layer one of the lcd
    char value[16];   // e.g. "12:34", "5", "101.1"         layer two of the lcd


    bool is_visiable = false; // this will tell us if the page is visiaible 
    bool is_editiing = false; // this will tell us if we are editing the page
    bool is_editable = true; // so we can just the values set this to false and
                             // we cant change the values  

    ApplyFunc onApply;

    Page* next;
    Page* prev;
};