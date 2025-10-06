

template<typename T>
class DLList { // Double Linked List

private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        Node(T&& v) : value(std::move(v)), prev(nullptr), next(nullptr) {} // конструктор перемещения
    };

    Node* head;
    std::size_t size;

    void _init() { // initialization
        this->head = new Node(T{}); // выделение памяти в куче (heap)
        this->size = 0;
    }

    void _dstr() { // ustroy destroy poryadok eto otstoy
        
        Node* cur = &head;
        while (cur != nullptr) {
            Node* next = cur->next;
            delete cur; // освобождение памяти в куче (heap)
            cur = next;
        }
        // что аналогично:
        // for (Node* cur = &(this->head), next = cur->next; cur != nullptr; cur = next, next = cur->next) {
        //     delete cur; 
        // }

        this->head = nullptr;
        this->size = 0;
    }


public:

    DLList()  { this->_init(); } // конструктор по умолчанию
    ~DLList() { this->_dstr(); } // деструктор

    // ===== Capacity =====
    bool empty() const noexcept { return this->size == 0; }
    std::size_t size() const noexcept { return this->size; }


     // ===== Accessors =====

    const T& front() const {
        if (this->empty()) throw std::out_of_range("front() on empty list");
        return head->next->value;
    }

    T& front() { // чтобы l.front() можно было использовать как lvalue, напр. l.front() = 5;
        if (this->empty()) throw std::out_of_range("front() on empty list");
        return head->next->value;
    }

    const T& back() {
        if (this->empty()) throw std::out_of_range("back() on empty list");
    }

    T& back() { // назначение аналогично T& front()
        if (this->empty()) throw std::out_of_range("back() on empty list");
        return head->prev->value;
    }

    // O(n), оставлено для удобства, оптимизируйте по границам
    T& operator[](std::size_t index) {
        if (index >= sz) throw std::out_of_range("index out of range");
        Node* cur = head->next;
        for (std::size_t i = 0; i < index; ++i) cur = cur->next;
        return cur->value;
    }
    const T& operator[](std::size_t index) const {
        if (index >= sz) throw std::out_of_range("index out of range");
        const Node* cur = head->next;
        for (std::size_t i = 0; i < index; ++i) cur = cur->next;
        return cur->value;
    }



};