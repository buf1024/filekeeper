using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Management;

namespace ConsoleApplication1
{
    //class Program
    //{
    //    static void Main(string[] args)
    //    {
    //    }
    //}

    public class WMIProcessWatch
    {
        ManagementEventWatcher watch_crt = null;
        ManagementEventWatcher watch_del = null;

        public WMIProcessWatch()
        {
            Console.WriteLine("Waiting for an event...");

            StartWatchCreateProcess();
            StartWatchDeleteProcess();
        }

        ~WMIProcessWatch()
        {
            if (watch_crt != null)
                watch_crt.Stop();
            if (watch_del != null)
                watch_del.Stop();
        }

        private void StartWatchCreateProcess()
        {
            WqlEventQuery query = new WqlEventQuery("__InstanceCreationEvent",
                         new TimeSpan(0, 0, 1),
                         "TargetInstance isa \"Win32_Process\"");
            watch_crt = new ManagementEventWatcher(query);
            watch_crt.EventArrived += new EventArrivedEventHandler(HandleProcessCreateEvent);
            watch_crt.Start();
        }

        private void StartWatchDeleteProcess()
        {
            WqlEventQuery query = new WqlEventQuery("__InstanceDeletionEvent",
                         new TimeSpan(0, 0, 1),
                         "TargetInstance isa \"Win32_Process\"");
            watch_del = new ManagementEventWatcher(query);
            watch_del.EventArrived += new EventArrivedEventHandler(HandleProcessDeleteEvent);
            watch_del.Start();
        }

        private void HandleProcessCreateEvent(object sender,
                    EventArrivedEventArgs e)
        {
            Console.WriteLine("Win32_Process event: Process Created.");
            ReportEventMessage(e);
        }

        private void HandleProcessDeleteEvent(object sender,
                    EventArrivedEventArgs e)
        {
            Console.WriteLine("Win32_Process event: Process Deleted.");
            ReportEventMessage(e);
        }

        private void ReportEventMessage(EventArrivedEventArgs e)
        {
            ManagementBaseObject o = e.NewEvent; //__InstanceCreationEvent
            ManagementBaseObject mo = (ManagementBaseObject)o["TargetInstance"];//Win32_Process
            Console.WriteLine("Name={0},ExecPath={1},CommandLine={2}",
                mo["Name"], mo["ExecutablePath"], mo["CommandLine"]);
        }

        public static void Main()
        {
            WMIProcessWatch wmipw = new WMIProcessWatch();
            Console.ReadLine();
        }
    }
 


}
