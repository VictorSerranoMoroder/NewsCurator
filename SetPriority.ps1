

# Get all Python processes
$pythonProcesses = Get-Process | Where-Object { $_.ProcessName -eq 'python' }

# Increase CPU priority for each Python process
foreach ($process in $pythonProcesses) {
    $process.PriorityClass = 'RealTime'
    Write-Host "Increased CPU priority for process $($process.Id): $($process.ProcessName)"
}

pause