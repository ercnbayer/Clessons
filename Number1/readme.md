void EncodeString(TCHAR *pKey , TCHAR* pStrIn, TCHAR *pStrOut) {
	
	int i, e ,c , k , v;
	e = _tcslen(pStrIn) - 1;
	k = _tcslen(pKey);
	i = c = 0;
	TCHAR ch = 0;
	
	while( i <= e ) {

		ch = pStrIn[i];
		for (v = 0; v < k; v++) {
			ch = ch ^ pKey[v];
		}

		pStrOut[c++] = ch;
		if (i == e)
			break;

		ch = pStrIn[e];
		for (v = 0; v < k; v++) {
			ch = ch ^ pKey[v];
		}

		pStrOut[c++] = ch;
		e--;
		i++;
	}

}
//I Decoded This Crypto Algorithm which stated as "EncodeString".

void DecodeString(TCHAR* pKey, TCHAR* pStrEncoded, TCHAR* pStrOut) {	

	int i, e,g, c, k, v;
	e = _tcslen(pStrEncoded)-1 ;
	k = _tcslen(pKey);
	 c = 0;
	 g = 0;
	 i = 0;
	TCHAR ch = 0;
	
	while (i <= e) {
		
		ch = pStrEncoded[g++];
		for (v = 0; v < k; v++)
			ch = ch ^ pKey[v];
		pStrOut[c++] = ch;
	
		
		

		if (i == e)
			break;
		ch = pStrEncoded[g++];
		for (v = 0; v < k; v++)
			ch = ch ^ pKey[v];
		pStrOut[e]=ch;
		i++;
		e--;

	}
						}
