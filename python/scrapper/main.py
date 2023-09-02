import mechanicalsoup
browser = mechanicalsoup.StatefulBrowser()
browser.open("http://httpbin.org/")
print(browser)