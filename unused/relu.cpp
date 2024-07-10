#include <iostream>

extern "C" {

    class ReLU {
    private:
        int* input;
        int* output;
        int size;
    public:
        ReLU(int size) : size(size) {
            output = new int[size];
        }

        void set_input(int* input_ptr) {
            input = input_ptr;
        }

        void activate() {
            if (input == nullptr) {
                std::cerr << "Error: Null pointer input." << std::endl;
                return;
            }

            for (int i = 0; i < size; i++) {
                output[i] = input[i] > 0 ? input[i] : 0;
            }
        }

        void print() const {
            std::cout << "input: Arr[" << size << "]" << std::endl;
        }
    };

    ReLU* ReLU_new(int size) {
        return new ReLU(size);
    }

    void ReLU_set_input(ReLU* relu, int* input_ptr) {
        relu->set_input(input_ptr);
    }

    void ReLU_activate(ReLU* relu) {
        relu->activate();
    }

    void ReLU_print(const ReLU* relu) {
        relu->print();
    }

}

// int main() {
//     int values[] = {5, -3, 8, -1, 0, 7};
//     int size = sizeof(values) / sizeof(values[0]);

//     ReLU relu(size);
//     relu.print(); 

//     return 0;
// }