#include <iostream>
#include <vector>
#include <algorithm>

// This outputs a vector of integers. 
// Notice that we pass the vector by reference.
void outv(std::vector<int>& v) {
  for (int &e : v) {
    std::cout << e << "\n";
  }
  std::cout << "\n";
}

// We use this as a sample object that holds a value.
// This will be an element of vector<Box>.
class Box {
public:
  int v; // Publicly accessible, just for examples.
  void square() { v *= v; } // Modifies the Box.
};


int main() {

  std::cout << "---\nvector<int> tests\n";

  int x {1};
  int y {2};
  int z {3};
  std::vector<int> iv {x,y,z};

  // Output the elements using a "for" over the vector.
  for (int& e : iv) {
    std::cout << e << "\n";
  }
  std::cout << "\n";

  // Modifying the variables used in the iv initializer...
  x+=10;
  y+=10;
  z+=10;
  // ... does not modify the contents of the vector (unsurprisingly).
  for (int& e : iv) {
    std::cout << e << "\n";
  }
  std::cout << "\n";

  // Note that we can directly modify the elements of the vector...
  for (int& e : iv) {
    // ... the iteration gives us a "handle" on the storage for each element.
    // That's because e is of type int&.
    e += 100;
  }
  std::cout << "\n";

  // Here you will see the changes.
  for (int& e : iv) {
    std::cout << e << "\n";
  }
  std::cout << "\n";

  // Here is another way of iterating, relying on the built-in "random
  // access" iterator that comes with class vector.
  //
  // p is the name of the iterator. iv.begin() starts it at the first 
  // item. ++p advances it. We can test iterators for equality. This 
  // is defined to be whether the iterators are referring to the same
  // item in the vector. Thus, even though iv.end() returns an iterator
  // referencing "just beyond the last item in the vector", you can 
  // check whether or not p has gotten there, using == and !=.
  // 
  // Note that C++ has overloaded * so that (*p) means "the contents
  // of the vector's item referenced by iterator p." We can read those
  // contents and change those contents.
  for (std::vector<int>::iterator p = iv.begin(); p != iv.end(); ++p) {
    (*p) += 2000;
  }
  // Changes seen here, using the same kind of notation.
  for (std::vector<int>::iterator p = iv.begin(); p != iv.end(); ++p) {
    std::cout << (*p) << "\n";
  }
  std::cout << "\n";

  // Yet another way, using the overloaded operator[]. It returns
  // a reference to that integer element in the vector.
  for (int i=0; i < iv.size(); i++) {
    iv[i] += 30000;
  }
  // This operator can also be used for reading the element's value,
  // as used below.
  for (int i=0; i < iv.size(); i++) {
    std::cout << iv[i] << "\n";
  }
  std::cout << "\n";

  // By the way, this code below doesn't work. This isn't Python, but
  // rather an "industrial language". C++ doesn't give you all the
  // conveniences.
  //
  //std::cout << iv << "\n";


  // Okay, now let's play with vector<Box>...
  std::cout << "---\nvector<Box> tests\n";

  Box a {4};
  Box b {5};
  Box c {6};
  std::vector<Box> bv {a,b,c};

  // Same kind of iteration.
  for (Box& e : bv) {
    std::cout << e.v << "\n";
  }
  std::cout << "\n";

  // Modifying the stack objects used in the intializer...
  a.v += 20;
  b.v += 20;
  c.v += 20;
  
  // ...does not modify the vector's. We're learning below that the
  // constructor makes its own storage for its items, and copies
  // each object into that storage. Not a surprise, but good to
  // know.
  //
  for (Box& e : bv) {
    std::cout << e.v << "\n";
  }
  std::cout << "\n";

  // This will modify each vector item's v attribute.
  for (Box& e : bv) {
    e.v += 200;
  }
  // Here we are using operator[] again, but now for the Box.
  for (int i=0; i<bv.size(); i++) {
    std::cout << bv[i].v << "\n";
  }
  std::cout << "\n";

  // Here we modify an item using the operator[].
  bv[1].square();
  
  // By the way, using operator[] does not lead to any "bounds
  // checking." C++ will assume you know that the index given
  // is valid. If you want that checking, you can use the 
  // method bv.at(i) instead of bv[i].
  
  // Here is use of the iterator. Notice that the -> operation
  // is overloaded, too, just as we saw * was up above.
  for (std::vector<Box>::iterator p = bv.begin(); p != bv.end(); p++) {
    std::cout << p->v << "\n";
  }
  std::cout << "\n";

  // Vectors support lengthening with stack-like operations.
  //
  // We can push on an additional element, increasing the size
  // of the vector by 1.
  bv.push_back(Box {7});

  for (auto e : bv) {
    // I haven't ever shown you "auto," have I?
    std::cout << e.v << "\n";
  }
  std::cout << "\n";

  // We can pop off the last element, decreasing the size of the
  // vector by 1.
  bv.pop_back();

  for (auto e : bv) {
    std::cout << e.v << "\n";
  }
  std::cout << "\n";

  // You can also perform chunks of "pushes", but filling the extra
  // new size with the default/"zero" element. The code below adds
  // seven 0s to the end.
  iv.resize(10);

  // You can offset the iterator (because it is a "random access" 
  // iterator using notation that looks like "pointer arithmetic."
  // This will set iv[6] to 4567.
  std::vector<int>::iterator place = iv.begin()+6;
  (*place) = 4567890;

  // Output those changes.
  outv(iv);

  // You can insert elements at insertion points specified by an
  // iterator. This will be expensive for large vectors, as C++
  // will have to move the contents, and may even reallocate the
  // contents, of the vector's items.
  iv.insert(iv.begin()+4,987);
  outv(iv);

  // You can remove contiguous chunks of items. This shrinks the
  // size of the vector. 
  iv.erase(iv.begin()+2,iv.end()-4);
  outv(iv);

  // There is "clear" for erasing everything.
  // iv.clear()
  //
  // There is "reserve" for increasing the capacity, without changing
  // the size.
  // iv.reserve(new_capacity)
  //

  // Did I mention that C++ has a sorting algorithm that works for 
  // any type? It relies on you providing a "function object", an
  // instance of a class that overrides operator(). That operator
  // on that object takes two arguments, and returns a bool indicating
  // whether the first is less than the second.
  //
  sort(iv.begin(), iv.end(), std::greater<int>());
  outv(iv);
  //
  // C++ people seem real prahd of this. It is a result of including
  // the <algorithm> STL.
  //
  // You would normally use std::less<int>(), but I got this example
  // from the C++ inventor.

}
