import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLabel, QLineEdit, QPushButton, QMessageBox, QTableWidget, QTableWidgetItem, QInputDialog
from PyQt5.QtCore import Qt
import ctypes

# Load the C++ shared library
book_lib = ctypes.CDLL('./libxx.so')

# Define Book structure
class Book:
    def __init__(self, author, isbn, title):
        self.author = author
        self.isbn = isbn
        self.title = title
        self.checked_out = False
        self.checkout_date = 0

# Create Skip List interface
class SkipList:
    def __init__(self):
        self.book_lib = ctypes.CDLL('./libbook.so')
        self.book_lib.create_book_db.restype = ctypes.c_void_p
        self.book_db = self.book_lib.create_book()

    def add_book(self, author, isbn, title):
        author_cstr = ctypes.c_char_p(author.encode('utf-8'))
        isbn_cstr = ctypes.c_char_p(isbn.encode('utf-8'))
        title_cstr = ctypes.c_char_p(title.encode('utf-8'))
        self.book_lib.add_book(self.book_db, author_cstr, isbn_cstr, title_cstr)

    def check_out_book(self, isbn):
        isbn_cstr = ctypes.c_char_p(isbn.encode('utf-8'))
        result = self.book_lib.check_out_book(self.book_db, isbn_cstr)
        return bool(result)

    def return_book(self, isbn):
        isbn_cstr = ctypes.c_char_p(isbn.encode('utf-8'))
        result = self.book_lib.return_book(self.book_db, isbn_cstr)
        return bool(result)

    def is_book_available(self, isbn):
        isbn_cstr = ctypes.c_char_p(isbn.encode('utf-8'))
        result = self.book_lib.is_book_available(self.book_db, isbn_cstr)
        return bool(result)

    def calculate_fine(self, isbn, overdue_days, fine_per_day):
        isbn_cstr = ctypes.c_char_p(isbn.encode('utf-8'))
        fine = self.book_lib.calculate_fine(self.book_db, isbn_cstr, overdue_days, fine_per_day)
        return fine

# Main Application Window
class LibraryApp(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Library Management System')
        self.resize(600, 400)

        self.init_ui()

    def init_ui(self):
        # Widgets
        self.author_input = QLineEdit()
        self.isbn_input = QLineEdit()
        self.title_input = QLineEdit()
        self.add_button = QPushButton('Add Book')
        self.checkout_button = QPushButton('Check Out')
        self.return_button = QPushButton('Return')
        self.is_available_button = QPushButton('Check Availability')
        self.fine_button = QPushButton('Calculate Fine')
        self.result_label = QLabel()

        # Book Table
        self.book_table = QTableWidget()
        self.book_table.setColumnCount(3)
        self.book_table.setHorizontalHeaderLabels(['ISBN', 'Author', 'Title'])

        # Layout
        main_layout = QVBoxLayout()

        input_layout = QHBoxLayout()
        input_layout.addWidget(QLabel('Author:'))
        input_layout.addWidget(self.author_input)
        input_layout.addWidget(QLabel('ISBN:'))
        input_layout.addWidget(self.isbn_input)
        input_layout.addWidget(QLabel('Title:'))
        input_layout.addWidget(self.title_input)
        input_layout.addWidget(self.add_button)

        action_layout = QHBoxLayout()
        action_layout.addWidget(self.checkout_button)
        action_layout.addWidget(self.return_button)
        action_layout.addWidget(self.is_available_button)
        action_layout.addWidget(self.fine_button)

        main_layout.addLayout(input_layout)
        main_layout.addWidget(self.result_label)
        main_layout.addLayout(action_layout)
        main_layout.addWidget(self.book_table)

        self.setLayout(main_layout)

        # Connect Signals
        self.add_button.clicked.connect(self.add_book)
        self.checkout_button.clicked.connect(self.check_out_book)
        self.return_button.clicked.connect(self.return_book)
        self.is_available_button.clicked.connect(self.check_availability)
        self.fine_button.clicked.connect(self.calculate_fine)

    def add_book(self):
        author = self.author_input.text()
        isbn = self.isbn_input.text()
        title = self.title_input.text()

        if not author or not isbn or not title:
            QMessageBox.warning(self, 'Error', 'Please enter all fields.')
            return

        # Add book to the database
        library.add_book(author, isbn, title)

        # Update book table
        self.update_book_table()

        self.result_label.setText('Book added successfully.')

    def check_out_book(self):
        isbn = self.isbn_input.text()

        if not isbn:
            QMessageBox.warning(self, 'Error', 'Please enter ISBN.')
            return

        if library.check_out_book(isbn):
            self.result_label.setText('Book checked out successfully.')
        else:
            self.result_label.setText('Book is not available.')

    def return_book(self):
        isbn = self.isbn_input.text()

        if not isbn:
            QMessageBox.warning(self, 'Error', 'Please enter ISBN.')
            return

        if library.return_book(isbn):
            self.result_label.setText('Book returned successfully.')
        else:
            self.result_label.setText('Book is already available.')

    def check_availability(self):
        isbn = self.isbn_input.text()

        if not isbn:
            QMessageBox.warning(self, 'Error', 'Please enter ISBN.')
            return

        if library.is_book_available(isbn):
            self.result_label.setText('Book is available.')
        else:
            self.result_label.setText('Book is not available.')

    def calculate_fine(self):
        isbn = self.isbn_input.text()

        if not isbn:
            QMessageBox.warning(self, 'Error', 'Please enter ISBN.')
            return

        overdue_days, ok = QInputDialog.getInt(self, 'Overdue Days', 'Enter the number of overdue days:')
        if not ok:
            return

        fine_per_day, ok = QInputDialog.getDouble(self, 'Fine Per Day', 'Enter the fine amount per day:')
        if not ok:
            return

        fine = library.calculate_fine(isbn, overdue_days, fine_per_day)
        self.result_label.setText(f'Fine for overdue book: ${fine:.2f}')

    def update_book_table(self):
        # Clear table
        self.book_table.setRowCount(0)

        # Fetch books from the database
        # For this example, let's assume we have a function get_books() in the C++ library that returns a list of books
        books = []  # library.get_books()

        # Populate table
        for row, book in enumerate(books):
            self.book_table.insertRow(row)
            self.book_table.setItem(row, 0, QTableWidgetItem(book.isbn))
            self.book_table.setItem(row, 1, QTableWidgetItem(book.author))
            self.book_table.setItem(row, 2, QTableWidgetItem(book.title))


if __name__ == '__main__':
    app = QApplication(sys.argv)

    # Initialize SkipList interface
    library = SkipList()

    window = LibraryApp()
    window.show()

    sys.exit(app.exec_())
