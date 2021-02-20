/*
*HASHTABLE.H IMPLEMENTATION
*COLIN MACRAE
*11/18/20
*/

/*PRIVATE FUNCTIONS*/
template <typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
	for( auto & thisList : table) // for each list in table
		thisList.clear();		// clear the lists
}

template <typename K, typename V>
void HashTable<K, V>::rehash() // rehash function called when numEntries > size of table  
{
	std::vector<std::list<std::pair<K,V>>> oldTable = table; // copy table over before rehashing
	
	table.resize(prime_below( 2 * table.size() ) );				// resize the table to double the size 	
		makeEmpty();									// clear the table 
	
	currentSize = 0;
	
	for(auto & thisList :oldTable)						// deep copy of table 
		for(auto & thisPair : thisList)
			insert(std::move(thisPair));

	
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) 
{
	static std::hash<K> hf; // using hash function for type k from STL 
	return hf(k) % table.size();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

template <typename K, typename V>
HashTable<K,V>::HashTable( size_t size) : table(prime_below(size)) , currentSize(0)
{
	std::cout << prime_below(size); // for passServer...
}
// creates new hashtable with size of the prime below size parameter

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
	makeEmpty();	// clear the internal hashtable vector and lists 
	
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K &k) // determines if the key is within the hash table's vector bounds 
{
	if(myhash(k) >= 0 && myhash(k) < table.size()) // if key is within bounds of the hashtable 
	{
		auto & whichList = table[myhash(k)];
		auto itr = begin(whichList); 	
		std::list<K> keys;
		while(itr != end(whichList)) // copy the pairs' key values into a list of keys to check 
			keys.push_back(std::get<0>(*itr++));
		return find( begin(keys), end(keys), k) != end(keys); 
	}
	// if this point is reached, the table doesn't contain k, so return false 
		return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K,V> &kv) 
{
	if(contains(std::get<0>(kv))) // if the key is within the table
	{
		auto & whichList = table[myhash(std::get<0>(kv))]; // get the list pretaining to the hashed key 
		return find( std::begin( whichList ), end( whichList ), kv ) != end(whichList); // try to find the specified pair and return result
	}else
		return false;			// if key isn't contained in the hashtable, the pair can't be 
	
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K,V> &kv) 
{
	if(!match(kv)) // if table doesnt already contain key/value pair 
	{	
		if( size() > table.size()) // if number of contents is greater than the table size, increase/rehash
			rehash();
		if(contains(std::get<0>(kv))) // if the table contains the kv pair, update the value
		{
			auto & whichList = table[myhash(std::get<0>(kv))]; // pull out list pertaining to hashed key of input
			auto itr = begin(whichList); 						// instantiate iterator at beginning of list 
			while(std::get<0>(*itr) != std::get<0>(kv))			//while the iterator's pair's value =\= parameter pair's value, ++
				itr++;
			*itr = kv;  // swap contents of list pair and parameter 
		}else //
		{
			table[myhash(std::get<0>(kv))].push_back(kv); // push pair<K,V> into bucket list at hashed index of key k 
			currentSize++; // increment size 
		}
		
		return true;
	}
	
	return false;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K,V> &&kv) 
{
if(!match(kv)) // if table doesnt already contain key/value pair 
	{	

		if( size() > table.size()) // if number of contents is greater than the table size, increase/rehash
			rehash();
			
		if(contains(std::get<0>(kv))) // if the table contains the kv pair, update the value
		{
			auto & whichList = table[myhash(std::get<0>(kv))]; // pull out list pertaining to hashed key of input
			auto itr = begin(whichList); 						// instantiate iterator at beginning of list 
			while(std::get<0>(*itr) != std::get<0>(kv))			//while the iterator's pair's value =\= parameter pair's value, ++
				itr++;
			*itr = kv;  // update contents of list pair and parameter 
		}else //
		{
			table[myhash(std::get<0>(kv))].push_back(std::move(kv)); // push pair<K,V> into bucket list at hashed index of key k 
			currentSize++; // increment size 
		}
		
		return true;
	}
	
	return false;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K &k) 
{
	
	auto & whichList = table[myhash(k)]; // pull out list pertaining to hashed key of input
	auto itr = begin(whichList); 						// instantiate iterator at beginning of list 
	while(std::get<0>(*itr) != k && itr != end(whichList))			//while the iterator's pair's value =\= parameter pair's value, ++
		itr++;
		
	if(itr == end(whichList)) // if the iterator reached the end, the pair with the matching key wasn't in the list 
		return false;
								// if this point was reached, the pair with the appropriate key was in the list, so erase it
	whichList.erase(itr);
	--currentSize;				// adjust size appropriately 
	return true;
}

template <typename K, typename V>
void HashTable<K, V>::clear()
{
	makeEmpty();			// use internal function to empty the table's lists 
	currentSize = 0; 			//update size appropriately 
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char * filename) // load file 
{
	bool success = true;
	clear(); // clear HashTable of any current data
	
	std::ifstream ifs; 
	std::pair<K,V> * p;	
	K k;
	V v;
	ifs.open(filename, std::ios::in); // open input file stream 
	
	do{			//while there are keys in the file, read them and inset them into the hashtable 
		
		ifs >> k;
		ifs >> v;
		p = new std::pair<K,V>(k,v);
		insert(*p);
	}while(!ifs.eof() && !ifs.fail() && ifs.good());
	
	if(ifs.fail() || !ifs.good()) // if the input stream failed, report failure 
		success = false;
	
	ifs.close();
	
	return success;
}

template <typename K, typename V>
void HashTable<K, V>::dump() // print out the hashtable 
{	int i = 0;
	
	for(auto & thisList: table)
	{
		std::printf("v[%u]: ", i); //print indices of hashtable 

		auto itr = begin(thisList);			//for each chained list in the bucket ,iterate through and print elements 
		while(itr != end(thisList))
		{
			if(itr!= end(thisList)-- && itr!= begin(thisList)) // if there's more than onelement in bucket, separate with colon 
				std::cout << ":";
			std::cout << std::get<0>(*itr) << " " << std::get<1>(*itr); // print key and value pair 
			
			itr++;
		}
		std::cout << "\n"; //for each list, print endl 
		i++;
	}
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename) // write to file specified with filename parameter 
{
	bool success = true;
	std::ofstream ofs(filename, std::ofstream::out);
	for(auto & thisList : table) // for each list in the table, write the key value pair separated by an endl 
		for(auto & pair : thisList)
			ofs << std::get<0>(pair) << " " << std::get<1>(pair) << "\n";
			
			
	if(ofs.bad())
		success = false;
	
	ofs.close(); // close file after hashtable is written and report success or failure of writing
	
		return success;
}

template <typename K, typename V>
size_t HashTable<K, V>::size() // return number of entries in the hashtable 
{
	return currentSize;
}

