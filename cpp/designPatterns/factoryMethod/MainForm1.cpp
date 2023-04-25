class MainForm : public Form {
  TextBox* txtFilePath;
  TextBox* txtFileNumber;
  ProgressBar* progressBar;

 public:
  void Button1_Click() {
    string filepath = txtFilePath->getText();
    int number = atoi(txtFileNumber->getText().c_str());

    FileSplitter* splitter = new FileSplitter(filepath, number);
    splitter->split();
  }
}