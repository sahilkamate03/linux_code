import mechanicalsoup
import pandas as pd

browser = mechanicalsoup.StatefulBrowser()
url = "http://14.139.108.229/W27/login.aspx"

browser.open(url)
browser.get_current_page()
browser.select_form()
browser.get_current_form().print_summary()

browser["txtUserName"] = 21185
browser["Password1"] = "MEMBER"

response = browser.submit_selected()

new_url ="http://14.139.108.229/W27/MyInfo/w27MyInfo.aspx"
browser.open(new_url)

page = browser.get_current_page()
table = page.find_all('table', attrs={"id" : "ctl00_ContentPlaceHolder1_CtlMyLoans1_grdLoans"})

if table:
  tds = table[0].find_all("td")
  book_data= []
  for td in tds:
    book_data.append(td.text.replace("\n",""))

  no_of_book_issued = int(len(book_data)/9)

num_columns = 9
data_rows = [book_data[i:i+num_columns] for i in range(0, len(book_data), num_columns)]

columns = ['AccNum', 'Title', 'Author', 'Borrowed On', 'Due On', 'Status', 'Recalled', 'FineDue', 'Reissue']
df = pd.DataFrame(data_rows, columns=columns)

reissue_btns = table[0].find_all("input")
issue_book_btn = []
for btn in reissue_btns:
    issue_book_btn.append(btn.attrs["name"])

df["Reissue"] = issue_book_btn

indian_current_date = datetime.now(pytz.timezone('Asia/Kolkata')).date()

for index, row in df.iterrows():
    due_date_str = row['Due On']
    due_date = datetime.strptime(due_date_str.strip(), "%d-%b-%Y").date()

    if due_date <= indian_current_date:
        browser.select_form('form[action="./w27MyInfo.aspx"]')
        browser.submit_selected(btnName=row['Reissue'])
        print('Book Reissued')