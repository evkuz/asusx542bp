#01 15.11.2020 Рабочий вариант. Открывает mail.ru и считыват страничку.
from urllib.request import urlopen
from urllib.parse import urljoin

from lxml.html import fromstring

#URL='http://proglive.ru/courses'
URL='http://mail.ru'
ITEM_PATH='.our-courses_list .our-courses_item'


def parse_courses():
    f = urlopen(URL)
    print(f)
    list_html = f.read().decode('UTF-8')
    print(list_html)


def main():
    parse_courses()


if __name__ == '__main__':
    main()