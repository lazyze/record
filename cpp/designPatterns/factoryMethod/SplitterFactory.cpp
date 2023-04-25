class SplitterFactory({
    public:
    ISplitter* CreateSplitter() {
        return new BinarySplitter(...);
    }
}

class ISplitter {
 public:
  virtual void ISplitter() = 0;
  virtual ~ISplitter() {}
}
