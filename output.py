
def fibo(n):

	if(n==0):

		return 1;

	if(n==1):

		return 1;

	return fibo(n-1)+fibo(n-2);

def main():

	
	r = input();
	q=fibo(r);
	print("%d %d")%(r,q);

main()
