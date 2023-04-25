class ISplitter {
 public:
  virtual void ISplitter() = 0;
  virtual ~ISplitter() {}
}

class BinarySplitter : public ISplitter {
};

class TxtSplitter : public ISplitter {};

class PictureSplitter : public ISplitter {};

class VideoSplitter : public ISplitter {};
