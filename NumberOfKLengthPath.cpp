#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

const int64_t MODULUS = 1000000007;

struct Edge {
    int64_t vertex_from;
    int64_t vertex_to;
};

struct MatrixSize {
    int64_t number_of_strings;
    int64_t number_of_columns;
};

// Reading numbers
int64_t ReadNumber(std::istream& input = std::cin);

// Creating and reading edges
std::vector<Edge> ReadEdges(const int64_t& number_of_edges,
                            std::istream& input = std::cin);

// Writing a number of possible variants
void Write(const int64_t& ways, std::ostream& output = std::cout);

class Matrix {
 private:
    std::vector< std::vector<int64_t> > matrix_;
    MatrixSize size_;

 public:
     Matrix(const MatrixSize& size, const bool& digit) {
         std::vector< std::vector<int64_t> >
             matrix(size.number_of_strings,
                 std::vector<int64_t>(size.number_of_columns, 0));
         if (digit) {
             if (size.number_of_strings != size.number_of_columns) {
                 std::cout << "Impossible to create an identity matrix";
             }
             for (int i = 0; i < size.number_of_strings; ++i)
                 matrix[i][i] = 1;
         }
         matrix_ = matrix;
         size_ = size;
     }

     Matrix(const std::vector<Edge>& edges, const int64_t& size) {
         std::vector< std::vector<int64_t> >
             matrix(size,
                 std::vector<int64_t>(size, 0));
         for (int64_t i = 0; i < edges.size(); ++i) {
             matrix[edges[i].vertex_from][edges[i].vertex_to]++;
         }
         matrix_ = matrix;
         size_.number_of_strings = size;
         size_.number_of_columns = size;
     }

     int64_t Get(const int64_t& line,
                 const int64_t& column) const {
         if (line < 0 || line >= size_.number_of_strings || column < 0 ||
             column >= size_.number_of_columns) {
             std::cout << "Indexes of matrix are out of range";
         }
         return matrix_[line][column];
     }

     void Set(const int64_t& line,
              const int64_t& column,
              const int64_t& value) {
         if (line < 0 || line >= size_.number_of_strings || column < 0 ||
             column >= size_.number_of_columns) {
             std::cout << "Indexes of matrix are out of range";
         }
         matrix_[line][column] = value;
     }

     MatrixSize GetSize() const {
         return size_;
     }
};

bool MultiplicationPossible(const MatrixSize& size_of_left_matrix,
                            const MatrixSize& size_of_right_matrix) {
    const int64_t left_columns = size_of_left_matrix.number_of_strings;
    const int64_t right_strings = size_of_right_matrix.number_of_columns;
    if (left_columns == right_strings) {
        return true;
    }
    return false;
}
// Matrix Multiplication
Matrix MultiplicationOfMatrices(const Matrix& matrix_left,
                                const Matrix& matrix_right) {
    const MatrixSize size_of_left_matrix = matrix_left.GetSize();
    const MatrixSize size_of_right_matrix = matrix_right.GetSize();
    if (MultiplicationPossible(size_of_left_matrix,
                               size_of_right_matrix) == false) {
        std::cout << "Multiplication of matrixes is impossible";
    }
    MatrixSize size_result;
    size_result.number_of_strings = size_of_left_matrix.number_of_strings;
    size_result.number_of_columns = size_of_right_matrix.number_of_columns;
    Matrix matrix_result(size_result, false);
    for (int64_t i = 0; i < size_result.number_of_strings; ++i) {
        for (int64_t j = 0; j < size_result.number_of_columns; ++j) {
            for (int64_t k = 0; k < size_of_left_matrix.number_of_columns;
                ++k) {
                const int64_t number_of_ways_in_left = matrix_left.Get(i, k);
                const int64_t number_of_ways_in_right = matrix_right.Get(k, j);
                const int64_t current_number_of_ways = matrix_result.Get(i, j);
                const int64_t number_of_ways = ((number_of_ways_in_left *
                    number_of_ways_in_right) % MODULUS +
                    current_number_of_ways) % MODULUS;
                matrix_result.Set(i, j, number_of_ways);
            }
        }
    }
    return matrix_result;
}

// Exponentiation of a matrix
Matrix MatrixInPower(const Matrix& matrix, int64_t power) {
    Matrix delta_matrix = matrix;
    Matrix result_matrix(delta_matrix.GetSize(), true);
    while (power) {
        if (power % 2 != 0) {
            result_matrix = MultiplicationOfMatrices(result_matrix,
                delta_matrix);
        }
        delta_matrix = MultiplicationOfMatrices(delta_matrix, delta_matrix);
        power /= 2;
    }
    return result_matrix;
}

int64_t CountNumberOfWays(const int64_t& number_of_rooms,
                          const int64_t& path_length,
                          const std::vector<Edge>& edges) {
    const Matrix rooms_matrix(edges, number_of_rooms);
    const Matrix result_matrix = MatrixInPower(rooms_matrix, path_length);
    int64_t sum = 0;
    for (int64_t i = 0; i < number_of_rooms; ++i) {
        sum = (sum + result_matrix.Get(0, i)) % MODULUS;
    }
    return sum;
}

int64_t ReadNumber(std::istream& input) {
    int64_t value;
    input >> value;
    return value;
}

std::vector<Edge> ReadEdges(const int64_t& number_of_edges,
                            std::istream& input) {
    std::vector<Edge> edges;
    for (int64_t i = 0; i < number_of_edges; ++i)
    {
        Edge path;
        input >> path.vertex_from >> path.vertex_to;
        edges.push_back(path);
    }
    return edges;
}

std::vector<Edge> VertexIndexingOneToZero(std::vector<Edge> edges) {
    for (int64_t i = 0; i < edges.size(); ++i) {
        --edges[i].vertex_from;
        --edges[i].vertex_to;
    }
    return edges;
}

void Write(const int64_t& ways, std::ostream& output) {
    output << ways << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const auto& number_of_rooms = ReadNumber();
    const auto& number_of_edges = ReadNumber();
    const auto& path_length = ReadNumber();
    const auto& edges_not_checked_indexing = ReadEdges(number_of_edges);
    const auto& edges = VertexIndexingOneToZero(edges_not_checked_indexing);
    const auto& ways = CountNumberOfWays(number_of_rooms,
        path_length, edges);
    Write(ways);

    return 0;
}
