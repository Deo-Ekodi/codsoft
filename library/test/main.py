import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QLabel
import ctypes

# Load the C++ shared library
add_lib = ctypes.CDLL('./libaddition.so')

# Define the function prototype
add_func = add_lib.add
add_func.argtypes = [ctypes.c_int, ctypes.c_int]
add_func.restype = ctypes.c_int

class MyWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle('C++ Integration with PyQt5')
        self.setGeometry(100, 100, 300, 200)

        self.label = QLabel('Result: ', self)

        self.button = QPushButton('Add', self)
        self.button.clicked.connect(self.on_button_click)

        layout = QVBoxLayout()
        layout.addWidget(self.label)
        layout.addWidget(self.button)

        self.setLayout(layout)

    def on_button_click(self):
        a = 10
        b = 20
        result = add_func(a, b)
        self.label.setText(f'Result: {result}')

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())
