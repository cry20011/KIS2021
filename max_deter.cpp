#include <iostream>
#include <vector>


std::vector<std::vector<int>> GetMatr(std::vector<std::vector<int>>& matrix, int i, int j, int size) {
    std::vector<std::vector<int>> p(size, std::vector<int>(size));
    int ki, kj, di, dj;
    di = 0;
    for (ki = 0; ki < size - 1; ++ki) {
        if (ki == i) {
            di = 1;
        }

        dj = 0;
        for (kj = 0; kj < size - 1; ++kj) {
            if (kj == j) {
                dj = 1;
            }

            p[ki][kj] = matrix[ki + di][kj + dj];
        }
    }

    return p;
}

int Determinant(std::vector<std::vector<int>>& matrix, int size) {
    int j = 0;
    int det = 0;
    int k = 1;
    int n = size - 1;

    if (size == 1) {
        det = matrix[0][0];
        return det;
    }
    
    if (size == 2) {
        det = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
        return det;
    }
    
    if (size > 2) {
        for (int i = 0; i < size; ++i) {
            std::vector<std::vector<int>> p = GetMatr(matrix, i, 0, size);
            det = det + k * matrix[i][0] * Determinant(p, n);
            k = -k;
        }
    }
    
    return det;
}


void MatrixTransposeLeftRight(std::vector<std::vector<int>>& matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
}


void MatrixTransposeRightLeft(std::vector<std::vector<int>>& matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            std::swap(matrix[i][j], matrix[size - j - 1][size - i - 1]);
        }
    }
}



std::vector<std::vector<int>> SubmatrixTranspose(std::vector<std::vector<int>>& matrix, int left, int right, int up, int down, bool leftright) { 
    std::vector<std::vector<int>> trans_matrix = matrix;


    int submatrix_size = right - left + 1;
    std::vector<std::vector<int>> submatrix = std::vector<std::vector<int>>(submatrix_size, std::vector<int>(submatrix_size));

    for (int i = up; i < down + 1; ++i) {
        for (int j = left; j < right + 1; ++j) {
            submatrix[i - up][j - left] = matrix[i][j];
        }
    }


    if (leftright) {
        MatrixTransposeLeftRight(submatrix, submatrix_size);
    } else {
        MatrixTransposeRightLeft(submatrix, submatrix_size);
    }

    for (int i = up; i < down + 1; ++i) {
        for (int j = left; j < right + 1; ++j) {
            trans_matrix[i][j] = submatrix[i - up][j - left];
        }
    }

    return trans_matrix;
}



int main() {
    int size;
    std::cin >> size;
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }

    int max_det = Determinant(matrix, size);

    std::vector<std::pair<int, std::vector<std::vector<int>>>> matrixes{};
    matrixes.emplace_back(max_det, matrix);
    int prev_pos = 0;
    int iteration = 0;

    while (/*???*/ true) {
        int new_prev_pos = matrixes.size();

            for (int i = prev_pos; i < new_prev_pos; ++i) {

            for (int submatrix_size = 2; submatrix_size < size; ++submatrix_size) {
                for (int left = 0; left < size - submatrix_size + 1; ++left) {
                    for (int up = 0; up < size - submatrix_size + 1; ++up) {
                        auto new_matrix = SubmatrixTranspose(matrixes[i].second, left, left + submatrix_size - 1, up, up + submatrix_size - 1, 1);
                        
                        int det = Determinant(new_matrix, size);
                        std::cout << det << '\n';

                        matrixes.emplace_back(det, new_matrix);

                    }
                }


            }
        }

        prev_pos = new_prev_pos;
        ++iteration;
        int x = 0;
        std::cin >> x;
    }
   

}