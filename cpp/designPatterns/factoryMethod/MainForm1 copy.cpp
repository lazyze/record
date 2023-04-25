class MainForm : public Form {
  TextBox* txtFilePath;
  TextBox* txtFileNumber;
  ProgressBar* progressBar;

  SplitterFactory* factory;

 public:
  MainForm(SplitterFactory* factory) { this->factory = factory; }
  void Button1_Click() {
    string filepath = txtFilePath->getText();
    int number = atoi(txtFileNumber->getText().c_str());

    // FileSplitter* splitter = new FileSplitter(filepath, number);

    // ISplitter* splitter = new BinarySplitter(filepath, number);
    // //依赖具体类BinarySplitter

    // SplitterFactory factory;

    // SplitterFactory* factory = new BinarySplitterFactory();  //
    // 不能写在这里,通常写在构造

    ISplitter* splitter =
        factory->CreateSplitter();  // 间接依赖具体类BinarySplitter

    splitter->split();
  }
}

// MainForm只依赖抽象，不依赖具体类