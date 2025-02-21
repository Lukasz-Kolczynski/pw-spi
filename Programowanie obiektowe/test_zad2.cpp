/*
===================


zad 2


===================
*/



#include <iostream>
#include <vector>


template <typename T>
class Sorter
{
protected:
    std::vector<T>& data;
public:
    Sorter(std::vector<T>& v) : data(v) {}
    virtual void sort(bool descending) = 0;
    virtual ~Sorter() = default;
};


template <typename T>
class Dziel_i_rządźSorter : public Sorter<T> {
public:
    Dziel_i_rządźSorter(std::vector<T>& v) : Sorter<T>(v) {}
    void body(int left, int mid, int right, bool descending) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<T> leftArray(n1);
        std::vector<T> rightArray(n2);


        for (int i = 0; i < n1; i++) leftArray[i] = this->data[left + i];
        for (int i = 0; i < n2; i++) rightArray[i] = this->data[mid + 1 + i];      

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if ((descending && leftArray[i] > rightArray[j]) || (!descending && leftArray[i] < rightArray[j])) {
                this->data[k++] = leftArray[i++];
            } else {
                this->data[k++] = rightArray[j++];
            }
        }        
        
        while (i < n1) this->data[k++] = leftArray[i++];
        while (j < n2) this->data[k++] = rightArray[j++];
    
    }

    void bodySort(int left, int right, bool descending) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            bodySort(left, mid, descending);
            bodySort(mid + 1, right, descending);
            body(left, mid, right, descending);
        }
    }
    
    void sort(bool descending) override {
        bodySort(0, this->data.size() - 1, descending);
    }
};

/* O(n log n) */

int main() {
    std::vector<double> v{5.2, -5.1, 6, 10.001, 1111};    
    
    Dziel_i_rządźSorter<double> sorter(v);    
    
    std::cout << "Nieposortowane:\n";
    for (double num : v) std::cout << num << " " << std::endl;    
    
    sorter.sort(true);
    std::cout << "Posortowane malejąco:\n";
    for (double num : v) std::cout << num << " " << std::endl;    
    
    sorter.sort(false);
    std::cout << "Posortowane rosnąco:\n";
    for (double num : v) std::cout << num << " " << std::endl;
    
        return 0;
}