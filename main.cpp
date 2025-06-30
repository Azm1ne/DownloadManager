#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QTreeView>
#include <QFileSystemModel>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QTextEdit>
#include <QDebug>
#include <string>
#include <QMessageBox>

void RunCommandAsAdmin(const std::string& command) {
    std::string psCommand = "powershell -Command \"Start-Process powershell -ArgumentList '-NoProfile -ExecutionPolicy Bypass -Command " + command + "' -Verb RunAs\"";
    system(psCommand.c_str());
}

class DownloadLocationSelector : public QWidget {
    Q_OBJECT

public:
    DownloadLocationSelector(QWidget *parent = nullptr);

private slots:
    void setDownloadLocation();
    //void showAbout();

private:
    QFileSystemModel *model;
    QTreeView *tree;
    QLabel *label;
    QPushButton *confirmButton; //*aboutButton;
};

DownloadLocationSelector::DownloadLocationSelector(QWidget *parent) : QWidget(parent) {

    // file system model
    model = new QFileSystemModel();
    model->setRootPath(QDir::rootPath());

    // tree view and set the model
    tree = new QTreeView();
    tree->setModel(model);
    tree->setColumnWidth(0, 200);

    // label to show the selected download location
    label = new QLabel();
    label-> setText("Selected Download Location: None");

    // confirm button
    confirmButton = new QPushButton("Confirm");
    connect(confirmButton, &QPushButton::clicked, this, &DownloadLocationSelector::setDownloadLocation);

    // aboutButton = new QPushButton("About");
    // connect(aboutButton, &QPushButton::clicked, this, &DownloadLocationSelector::showAbout);

    // horizontal layout for the button and label
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(confirmButton);
    //buttonLayout->addWidget(aboutButton);
    buttonLayout->addWidget(label);

    // tree view and the button layout to the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(tree);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

// void DownloadLocationSelector::showAbout(){
//     QMessageBox::about(this, "About", "hellooooooo");
// }

void DownloadLocationSelector::setDownloadLocation() {
    QModelIndex index = tree->currentIndex();
    if (index.isValid()) {

        QString directory = model->filePath(index);
        std::string targetDir = directory.toStdString();

        std::string command = std::string("cd $env:USERPROFILE; Remove-Item -Recurse -Force Downloads; New-Item -ItemType SymbolicLink -Path $env:USERPROFILE\\Downloads -Target \"") + targetDir + "\"";

        qDebug() << "Command: " << QString::fromStdString(command);

        RunCommandAsAdmin(command);

        label->setText("Selected Download Location: " + directory);

        qDebug() << "Download location set to:" << directory;
    }
}

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QTabWidget *tabWidget;
    DownloadLocationSelector *downloadSelector;
    QTextEdit *aboutTab;
};

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {

    // tab widget
    tabWidget = new QTabWidget();

    // download location selector
    downloadSelector = new DownloadLocationSelector();
    tabWidget->addTab(downloadSelector, "Select Download Location");

    // "About" tab with some text
    aboutTab = new QTextEdit();
    aboutTab->setReadOnly(true);  // Make the text non-editable

    // Setting font size for the about tab
    QFont appFont = aboutTab->font();
    appFont.setPointSize(15);
    aboutTab->setFont(appFont);

    aboutTab->setText("This is a download manager application \n\n"
                      //"Version: 1.0\n"
                      "This application is a part of our course CSE 150.  Dept of CSE,  SUST");

    tabWidget->addTab(aboutTab, "About");

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(tabWidget);

    setLayout(mainLayout);

    setWindowTitle("Download Manager");
    setGeometry(500, 300, 600, 400);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"
