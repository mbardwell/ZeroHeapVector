#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    int n_bytes = argc > 1 ? atoi(argv[1]) : 1000000;

    char *l = static_cast<char *>(malloc(n_bytes));
    srand(time(nullptr));

    auto fillArray = [](char* array, int size) {
        for (int i = 0; i < size; ++i) {
            array[i] = rand() % 256;
        }
    };

    fillArray(l, n_bytes);

    free(l);
    return 0;
}
