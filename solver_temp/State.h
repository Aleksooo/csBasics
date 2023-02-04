template <typename T>
struct Iterator {
private:
    T* ptr;
public:
    Iterator() : ptr(nullptr) {}
    Iterator(T* ptr_) : ptr(ptr_) {}

    T* get_ptr() { return ptr; }

    Iterator operator++(int) { ptr++; return *this; }
    T operator*() { return *ptr; }
    bool operator!=(const Iterator<T>& lhs) { return (ptr != lhs.ptr); }
};


template <typename T, size_t dim>
class State {
public:
    typedef T my_type;
    State() : state(std::array<T, dim> {}) {}
    State(const std::array<T, dim>& coord) : state(coord) {}

    State(const State& lhs) {
        state = std::array<T, dim>();
        for (size_t i = 0; i<dim; i++) {
            state[i] = lhs.state[i];
        }
    }

    State& operator=(const State& lhs) {
        State t(lhs);
        std::swap(state, t.state);

        return *this;
    }

    State(State&& rhs) {
        state = std::array<T, dim>();
        for (size_t i = 0; i<dim; i++) {
            state[i] = rhs.state[i];
            rhs.state[i] = 0;
        }
    }

    State& operator=(State&& rhs) {
        State t(std::move(rhs));
        std::swap(state, t.state);

        return *this;
    }

    State& operator+=(const State& lhs) {
        for (size_t i = 0; i < state.size(); i++) {
            state[i] += lhs.state[i];
        }

        return *this;
    }

    State& operator-=(const State& lhs) {
        for (size_t i = 0; i < state.size(); i++) {
            state[i] -= lhs.state[i];
        }

        return *this;
    }

    friend State operator+(State lhs, const State& rhs) {
        lhs += rhs;
        return lhs;
    }

    friend State operator-(State lhs, const State& rhs) {
        lhs -= rhs;
        return lhs;
    }

    State operator*(T x) {
        State t(*this);
        for (size_t i = 0; i < state.size(); i++) {
            t[i] *= x;
        }

        return t;
    }

    State operator/(T x) {
        State t(*this);
        for (size_t i = 0; i < state.size(); i++) {
            t[i] /= x;
        }

        return t;
    }

    T& operator[](size_t i) { return state[i]; }
    size_t size() { return state.size(); }
    Iterator<T> begin() { return Iterator<T>(state.begin()); }
    Iterator<T> end() { return Iterator<T>(state.end()); }

    template <typename U, size_t dim_>
    friend std::ostream& operator<<(std::ostream& os, State<U, dim_>& obj);

private:
    std::array<T, dim> state;
};

template <typename T, size_t dim>
std::ostream& operator<<(std::ostream& os, State<T, dim>& obj) {
    for(auto i : obj.state) {
        os << i << "\t";
    }
    return os;
}
