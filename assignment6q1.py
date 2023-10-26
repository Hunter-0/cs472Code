from enum import Enum
import logging
# https://www.machinelearningplus.com/python/python-logging-guide/

class Severity(Enum):
    WARNING = 1
    ERROR = 2
    UNRECOVERABLE = 3


class Logger:
    def __init__(self):
        self._file = None

    def Startup(self, filename):
        self._file = open(filename, 'w')
        logging.basicConfig(stream=self._file, level=logging.DEBUG)

    def LogMessage(self, severity, service, message):
        if severity == Severity.WARNING:
            logging.warning(f'{service}: {message}')
        elif severity == Severity.ERROR:
            logging.error(f'{service}: {message}')
        elif severity == Severity.UNRECOVERABLE:
            logging.critical(f'{service}: {message}')

    def Shutdown(self):
        if self._file:
            self._file.close()


def programTester():
    logger = Logger()
    fileName = input("Enter the name of the log file: ")
    logger.Startup(fileName + ".txt")

    while True:
        severity = input('Enter severity of WARNING, ERROR, or UNRECOVERABLE or type q to exit: ')
        if severity == "q":
            break
        while severity not in Severity.__members__:
            severity = input('Invalid severity, enter WARNING, ERROR, or UNRECOVERABLE: ')
            if severity == "q":
                break

        service = input('Enter service: ')
        message = input('Enter message: ')

        logger.LogMessage(Severity[severity], service, message)

    logger.Shutdown()

programTester()
