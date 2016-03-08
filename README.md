# indexer

<p>In this Project we have used our Tokenizer and sorted list. We have modified tokenizer to work with the current project as we skip the special characters and we only return the alphanumeric and aplanatic characters as a token for every time we call getnexttoken.
We read the file through a buffer seek function that goes through the file and return back an str char pointer that we use later on and we pass in tokenizer and it return back tokens</p>
Sorted list is different than the old one as we have this time 2D sorted list as we also passing the file name along with each token which is associated with.
In the sorted list we took care of the counting when the compare function equals to zero we increment the token counter as we check for the file name as well.
We used recursion to open up the all sub directory along with the path so we can process each file individually through the steps. As we take care of all the files in the directory and the sub directories


<h3>Project Partners<h3>

<p>Mina Gadallah</p>
<p>Roberto Merino</p>
