#include <iostream>

using namespace std;

class Item {
  private:
    int id;
	string n;
	int qty;
	float c;

  public:

    Item() {
      int id = 0;
      string n = "";
      int qty = 0;
      float c = 0.00;
    }

  void getItem() {
    int id, qty;
    float c1;
    string n1;

    cout << "Enter  Item's no.: ";
    cin >> id;

    cout << "Enter Item's name: ";
    cin >> n1;

    cout << "Enter  Item's quantity: ";
    cin >> qty;

    cout << "Enter  Item's cost: ";
    cin >> c1;

    setID(id);
    setN(n1);
    setQ(qty);
    setC(c1);

  }
  void putItem() {
    cout << "ID = " << getID() << "\tName = " << getN() << "\tQuantity = " << getQ() << "\tCost = " << getC() << endl;
  }

  void setID(int id) {
    if (id > 0)
      this->id = id;
    else
      this->id = 0;
  }
  
  int getID() {
    return id;
  }

  void setN(string name) {
    n = name;
  }
  
  string getN() {
    return n;
  }

  void setQ(int qty) {
    if (qty > 0)
      this->qty = qty;
    else
      this->qty = 0;
  }
  int getQ() {
    return qty;
  }

  void setC(float cost) {
    if (cost > 0)
      c = cost;
    else
      c = 0;
  }

  float getC() {
    return c;
  }

  Item(int i1, string n1, int q1, float c1) {
    setID(i1);
    setN(n1);
    setQ(q1);
    setC(c1);
  }

  Item(int i1, string n1, int q1) {
    setID(i1);
    setN(n1);
    setQ(q1);
    c = 0.00;
  }

  Item(int i1, string n1, float c1) {
    setID(i1);
    setN(n1);
    qty = 0;
    setC(c1);
  }

  Item(const Item & obj) {
    this->id = obj.id;
    this->n = obj.n;
    this->qty = obj.qty;
    this->c = obj.c;
  }

  ~Item() {
    cout << "Destructor" << endl;
  }

  void setItem(int id, string name, int qty, float cost) {
    setID(id);
    setN(name);
    setQ(qty);
    setC(cost);
  }

  float getTotalCost() {
    if (getQ() >= 1)
      return getC() * getQ();
    
	return 0;

  }

  bool isEqual(const Item & obj) const {
    return (obj.id == this->id && n == obj.n && qty == obj.qty && c == obj.c);
  }

  void updateName(Item array[], int size) {
    for (int j = 0; j < size; j++) {
      if (this->id == array[j].id)
        array[j].n = n;
    }
  }

  Item getMinimumCostItem(Item array[], int size) {
    float min = array[0].c;
	int minIndex;
    for (int i = 0; i < size - 1; i++) {
      if (min > array[i].c) {
        min = array[i].c;
        minIndex = i;
      }
    }
    
    return array[minIndex];
  }

  float getAveragePrice(Item array[], int size) {
    float sum = 0.00;

    for (int i = 0; i < size; i++) {
      sum += array[i].c;
    }
    return sum / size;
  }

};

int main() {
  Item obj1, obj2, obj3;

  Item array[] = {
    obj1,
	obj2,
    obj3
  };

  obj1.getItem();
  obj2.getItem();
  obj3.getItem();

  obj1.putItem();
  obj2.putItem();
  obj3.putItem();

  return 0;
}
