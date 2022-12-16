import sys,subprocess, random, os

from PyQt5.QtWidgets import (
    QApplication, QDialog, QMainWindow, QMessageBox
)

from main_window_ui import Ui_MainWindow
from time import sleep

def make():
    subprocess.run(['make'], cwd='./pipe')
    subprocess.run(['make'], cwd='./socket')

class Window(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi(self)
        self.server = None
        self.client = None


    def run_server(self):
        serverLog = open("server.log", "w+")
        serverLog.write("")

        if self.server is not None:
            self.server.kill()

            self.server = None
        s = self.comboBox.currentIndex()
        if s == 1:
            self.server = subprocess.Popen(['./Server'], cwd='./pipe', stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        elif s == 2:
            self.server = subprocess.Popen(['./Server'], cwd='./socket', stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    def executeb(self):
        if self.server is None:
            return
            #dialog
        
        if self.client is not None:
            self.client.kill()
        
        s = self.comboBox.currentIndex()
        if s == 1:
            self.client = subprocess.Popen(['./Client'], cwd='./pipe', stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        elif s == 2:
            self.client = subprocess.Popen(['./Client'], cwd='./socket', stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        
        try:
            client_stdout, client_stderr = self.client.communicate(timeout=2)
        except subprocess.TimeoutExpired:
            self.client.kill()
            self.clientout.setHtml("Client timed out...")
            return
        if self.client.poll() is None:
            self.client.kill()
            self.clientout.setHtml("Client timed out...")
            return

        self.clientout.setHtml(client_stdout.decode("utf-8"))
        serverLog = open("server.log", "r")
        self.servout.setHtml(serverLog.read())

    def closeEvent(self, event):
        print("was here")
        if self.server is not None:
            self.server.kill()
        if self.client is not None:
            self.client.kill()
        event.accept()


if __name__ == "__main__":
    make()
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec())