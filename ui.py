import sys,subprocess, select, os

from PyQt5.QtWidgets import (
    QApplication, QDialog, QMainWindow, QMessageBox
)
from PyQt5.uic import loadUi

from main_window_ui import Ui_MainWindow

class Window(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi(self)

    def executeb(self):
        s = self.comboBox.currentIndex()
        serv = subprocess.Popen(["./serveurpipe"], stdout=subprocess.PIPE)

        poll = select.poll()
        poll.register(serv.stdout)

        cl = subprocess.run(["./clientpipe"], stdout=subprocess.PIPE)
        self.clientout.setHtml(cl.stdout.decode("utf-8"))
        
        rlist = poll.poll()
        fd = rlist[0]
        
        self.servout.setHtml(os.read(fd, 1024).decode("utf-8"))
        serv.kill()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec())