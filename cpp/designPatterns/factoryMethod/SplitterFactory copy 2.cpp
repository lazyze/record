
class BinarySplitterFactory : public SplitterFactory{
    public:
    virtual ISplitter* CreateSplitter(){
        return new BinarySplitter();
    }
}



class TxtSplitterFactory : public SplitterFactory{
    public:
    virtual ISplitter* CreateSplitter(){
        return new TxtSplitter();
    }
}

class PictureSplitterFactory : public SplitterFactory{
    public:
    virtual ISplitter* CreateSplitter(){
        return new PictureSplitter();
    }
}

class VideoSplitterFactory : public SplitterFactory{
    public:
    virtual ISplitter* CreateSplitter(){
        return new VideoSplitter();
    }
}



