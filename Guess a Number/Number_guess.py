import time

print("Mind Reader")
time.sleep(1)

print('\n Think a number between 1 to 100.')
input("Press Enter when you are ready ")

low = 1
high = 100

while low <= high:
    mid = (low + high) //2
    
    answer = input(f"\n Is your number grater than {mid}? (y/n)")
    
    if answer.lower() == "y":
        low = mid + 1
    else: 
        high = mid - 1 
        

print("\n Prediction Complete")
print("Your Number is :" , low)           

