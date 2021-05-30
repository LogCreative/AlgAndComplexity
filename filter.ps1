Get-ChildItem . '*.tex' -Force -Recurse | ForEach-Object -Process {
    $file = [io.Path]::Combine($_.DirectoryName, $_.FullName)

    (Get-Content $file)|
        ForEach-Object { $_ -replace '*******','Log Creative'} |  # Change Name
        ForEach-Object { $_ -replace '*******',''} | # Change Number
        Out-File $file -Force
}

Get-ChildItem .\ -recurse *-ZilongLi* | ForEach-Object {
    Rename-Item $_.FullName$_.FullName.Replace("-********","")
}