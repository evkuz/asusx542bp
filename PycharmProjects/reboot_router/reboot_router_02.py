# <input id="restartB" value="Перезагрузка" class="button button-blank" type="button">


from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC


def login2router():
    driver = webdriver.Chrome('/home/evkuz/PycharmProjects/chromedriver')
    driver.get('http://192.168.1.1')
    assert "S1500" in driver.title
    username = driver.find_element_by_xpath("//input[@value='Username']")
    username.clear()
    username.send_keys("admin")
    #
    passwd = driver.find_element_by_xpath("//input[@value='Password']")
    passwd.clear()
    passwd.send_keys("p9C8madU")
    button = driver.find_element_by_xpath("//input[@id='start']")
    button.click()

    try:
#        element = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.ID, "status-and-support")))
#        print("OK Im in")
        # over = element.find_element_by_link_text("Статус и поддержка")
        # over.click()
        #element = WebDriverWait(driver, 10).until(EC.element_to_be_clickable((By.LINK_TEXT, "Статус и поддержка"))).click()
        #                                                          "http://192.168.1.1/status-and-support.html#sub=1")))
        element = WebDriverWait(driver, 10).until(EC.element_to_be_clickable((By.XPATH, \
                                                                "//a[@href='status-and-support.html#sub=1']"))).click()
        print("Great")
#        over = driver.find_element_by_link_text("Статус и поддержка")
#        over.click()
        print("Now reboot !")
        import time
        time.sleep(2)
        try:
             oelement = WebDriverWait(driver, 10).until(EC.element_to_be_clickable((By.XPATH, \
                                                                                   "//a[@href='#sub=41']"))).click()
             print("ooooops")
#            over = driver.find_element_by_xpath("//a[@href='#sub=41']")
#            over.click()
             print("Link pressed")
             import time
             time.sleep(2)

             # НУ, теперь финальное нажатие кнопки !!!
             try:
                 # Rbutton = driver.find_element_by_id('restartB')
                 # Assert.assertEquals(true, Rbutton.isDisplayed())
                 # print("Button displayed")
                 # first = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.ID('restartB'))))
                  last = WebDriverWait(driver, 10).until(EC.element_to_be_clickable((By.XPATH, \
                                                                 "//input[@id='restartB']"))).click()
                  #assert last
#click()
                  #// *[ @ id = "restartB"]

#                rebutton = driver.find_element_by_xpath("//input[@id='restartB']")
#                rebutton.click()
                  print("Done")
             finally:
                driver.quit()


        finally:
            driver.quit()
    #    rest =
    finally:
        driver.quit()


#    print(driver.title)
#    over = driver.find_element_by_link_text("Статус и поддержка")
#    over.click()
#    element.click()
# http://192.168.1.1/status-and-support.html#sub=1


def main():
    login2router()


if __name__ == '__main__':
    main()
