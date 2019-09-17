struct Bitmap {
  uint8_t* data;
  ssize_t bytes;
  ssize_t size;
  ssize_t rows;
  ssize_t cols;

  Bitmap(int size) {
    this->bytes = size / 8 + 1;
    this->size = sizeof(uint8_t) * this->bytes;
    this->data = (uint8_t*)calloc(1, this->size);
  }
  Bitmap(int size_x, int size_y) {
    this->rows = size_x;
    this->cols = size_y;
    this->size = sizeof(uint8_t) * size_x * size_y;
    this->bytes = (size_x * size_y) / 8 + 1;
    this->data = (uint8_t*)calloc(1, this->size);
  }

  int get(int index) {
    int byte = index / 8;
    int offset = index % 8;
    return (this->data[byte] >> offset) & 1;
  }
  void set(int index, bool value) {
    int byte   = index / 8;
    int offset = index % 8;
    if(value) this->data[byte] |= (1 << offset);
    else      this->data[byte] &= ~(1 << offset);
  }
  void toggle(int index) {
    this->set(index, !this->get(index));
  }
  inline int  get2d(int x, int y) { return this->get((x * this->rows) + y); }
  inline void set2d(int x, int y, bool value) { set((x * this->rows) + y, value); }
  inline void toggle2d(int x, int y) { toggle((x * this->rows) + y); }
};
