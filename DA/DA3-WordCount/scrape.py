from urllib.request import urlopen

hadoopPage = "https://hadoop.apache.org"

page = urlopen(hadoopPage)

with open('F:\BE Assignments\LPI Assignments\DA\AIR3-WordCount','ab') as f:
	f.writelines(page)
