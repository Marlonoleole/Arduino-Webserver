#ifndef HASHMAP_H
#define HASHMAP_H

template <class V>
struct MapEntry {
  const char* key;
  V value;
  MapEntry* next;

  MapEntry(const char* key, V value) {
    this->key = key;
    this->value = value;
  }
  MapEntry(){
    this->next = 0;
  }
};

template <class V>
class StringMap {
  //TODO: add deconstructor
  //TODO: add that we can increase the array size if more items are added to keep the retrieval time constant on average
private:
  int capacity;
  int length;
  double loadBearing;
  MapEntry<V>* items;

   int indexint(char* key) {
    int sum = 0;
    char *p = key;
    while(*p){
      sum+=*p;
      p++;
    }
    return sum%(capacity-1);
  }
  
  int stringEquals(char* strn1, char* strn2){
    char *s1 = strn1;
    char *s2 = strn2;
    while(*s1 && *s2){
      if(*s1 != *s2){
        Serial.println("not Equals1");
        return 0;
    }
    s1++;
    s2++;
    }
   if(*s1!=0 || *s2!=0){
     Serial.println("not Equals2");
     return 0;
   }
   Serial.println("Equals");
   return 1;
 }

public:  
  StringMap() {
    this->capacity = 10;
    this->length = 0;
    this->loadBearing = 0.75;
    items = new MapEntry<V>[capacity]();
    for(int i=0;i<capacity; i++){
      items[i]= *new MapEntry<V>();
    }
  }

  int contains(char* key){
    int index = indexint(key);
    MapEntry<V> item = items[index];
    char* newKey = key;
    char* oldKey= item.key;
    while((item.next!=0)){
      if(stringEquals(newKey, oldKey)){
        return 1;
    }
      item = *item.next;
      oldKey = item.key;
    }
    return 0;
  }

  int putValue(char* key, V value) {
    int isthere = contains(key);
    if (isthere){
      return 0;
    }else{
      int index =indexint(key);
      MapEntry<V> theitem = items[index];
      MapEntry<V> newEntry (key,value);
      newEntry.next = &theitem;
      items[index]=newEntry;
      length++;
      return 1;
    }
  }

  V* getValue(char* key){
    int index = indexint(key);
    MapEntry<V> item = items[index];
    char* newKey = key;
    char* oldKey= item.key;
    while(item.next){
      if(stringEquals(newKey, oldKey)){
        return &(item.value);
      }
      item = *item.next;
      oldKey = item.key;
    }
    return 0;
  }
};
#endif
