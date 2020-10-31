#include <iostream>
#include <vector>
#include <utility>
#include <map>

const int64_t MODULUS = 1000000007;

struct Edge
{
    int64_t vertex_from;
    int64_t vertex_to;
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
    int64_t size_;
 public:
    int64_t GetSize() const;
    Matrix(const int64_t& matrix_size, const bool& digit);
    Matrix(const std::vector<Edge>& edges, const int64_t& matrix_size);
    int64_t get(const int64_t& line,
        const int64_t& column) const;
    void set(const int64_t& line, const int64_t& column,
        const int64_t& value);
};

int64_t Matrix::GetSize() const {
    return this->size_;
}

// Creating an identity matrix N*N, digit - 0 or 1
Matrix::Matrix(const int64_t& matrix_size, const bool& digit) {
    const std::vector<int64_t> str(matrix_size, 0);
    for (int64_t i = 0; i < matrix_size; ++i)
        this->matrix_.push_back(str);
    for (int64_t i = 0; i < matrix_size; ++i)
        this->matrix_[i][i] = int64_t(digit);
    this->size_ = matrix_size;
}

Matrix::Matrix(const std::vector<Edge>& edges, const int64_t& matrix_size) {
    this->size_ = matrix_size;
    std::vector<int64_t> str(matrix_size, 0);
    for (int64_t i = 0; i < matrix_size; ++i)
        this->matrix_.push_back(str);

    for (int64_t i = 0; i < edges.size(); ++i) {
        this->matrix_[edges[i].vertex_from - 1][edges[i].vertex_to - 1]++;
    }
}

int64_t Matrix::get(const int64_t& line,
    const int64_t& column) const {
    if (line < 0 || line >= matrix_.size() || column < 0 ||
        column >= matrix_[matrix_.size() - 1].size()) {
        std::cout << "indexes of matrix are out of range";
    }
    return this->matrix_[line][column];
}

void Matrix::set(const int64_t& line, const int64_t& column,
    const int64_t& value) {
    if (line < 0 || line >= matrix_.size() || column < 0 ||
        column >= matrix_[matrix_.size() - 1].size()) {
        std::cout << "indexes of matrix are out of range";
    }
    this->matrix_[line][column] = value;
}

// Matrix Multiplication
Matrix MultiplicationOfMatrices(const Matrix& matrix_left,
    const Matrix& matrix_right) {
    const int64_t matrix_size = matrix_left.GetSize();
    Matrix matrix_result(matrix_size, 0);
    for (int64_t i = 0; i < matrix_size; ++i)
        for (int64_t j = 0; j < matrix_size; ++j) {
            for (int64_t k = 0; k < matrix_size; ++k) {
                int64_t number_of_ways_in_left = matrix_left.get(i, k);
                int64_t number_of_ways_in_right = matrix_right.get(k, j);
                int64_t current_number_of_ways = matrix_result.get(i, j);
                int64_t number_of_ways = ((number_of_ways_in_left *
                                          number_of_ways_in_right) % MODULUS +
                                          current_number_of_ways) % MODULUS;
                matrix_result.set(i, j, number_of_ways);
            }
        }
    return matrix_result;
}

// Exponentiation of a matrix
Matrix MatrixInPower(const Matrix& matrix, int64_t power) {
    Matrix delta_matrix = matrix;
    Matrix result_matrix(delta_matrix.GetSize(), 1);
    while (power) {
        if (power & 1)
            result_matrix = MultiplicationOfMatrices(result_matrix,
                delta_matrix);
        delta_matrix = MultiplicationOfMatrices(delta_matrix, delta_matrix);
        power >>= 1;
    }
    return result_matrix;
}

int64_t CountNumberOfWays(const int64_t& number_of_rooms,
    const int64_t& path_length,
    const std::vector<Edge>& edges) {
    Matrix rooms_matrix(edges, number_of_rooms);
    rooms_matrix = MatrixInPower(rooms_matrix, path_length);
    int64_t sum = 0;
    for (int64_t i = 0; i < number_of_rooms; ++i)
        sum = (sum + rooms_matrix.get(0, i)) % MODULUS;
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

void Write(const int64_t& ways, std::ostream& output) {
    output << ways << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const auto& number_of_rooms = ReadNumber();
    const auto& number_of_edges = ReadNumber();
    const auto& path_length = ReadNumber();
    const auto& edges = ReadEdges(number_of_edges);
    const auto& ways = CountNumberOfWays(number_of_rooms,
        path_length, edges);
    Write(ways);

    return 0;
}
