count=0
for f in *; 
	do [[ -d "$f" ]] || count=$((count+1)); 
done
echo "$count"
